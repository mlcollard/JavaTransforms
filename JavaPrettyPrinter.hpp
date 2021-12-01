/*
    JavaPrettyPrinter.hpp

    Application built on JavaListener.
*/

#ifndef INCLUDED_JAVAPRETTYPRINTER_HPP
#define INCLUDED_JAVAPRETTYPRINTER_HPP

#include "JavaBaseListener.h"
#include <unordered_set>
#include <string>

class  JavaPrettyPrinter : public JavaBaseListener {
public:

    // constructor
    JavaPrettyPrinter(antlr4::Parser* parser)
        : parser(parser)
    {}

private:

    // parser
    antlr4::Parser* parser = nullptr;

    // entire output
    std::string pretty;

    // level of indent
    int indentationLevel = 1;

    // indentation string
    const std::string indentation = "    ";

    // generate a newline, removing any spaces first
    void newline() {
        if (pretty.back() == ' ' || pretty.back() == '\t')
            pretty.pop_back();

        pretty += "\n";
    }

    // indent according to the current indentation level
    void indent() {
        newline();
        for (int i = 0; i < indentationLevel; ++i)
            pretty += indentation;
    }

public:
    void enterMain(JavaParser::MainContext* /* ctx */) override {}

    void exitMain(JavaParser::MainContext* /* ctx */) override { 

        // fix newline missing at EOF
        if (pretty.back() != '\n')
            pretty += "\n";

        // output the entire pretty-printed program
        std::cout << pretty;
    }

    void enterNonblock(JavaParser::NonblockContext* /* ctx */) override {

        // // block statements handle their own indentation
        // if (ctx->start->getType() == JavaParser::LCURLY)
        //     return;

        // indent the statement and raise the indentation level for nested statements
        indent();
        ++indentationLevel;
    }

    void exitNonblock(JavaParser::NonblockContext* /* ctx */) override {

        // reduce the indentation for all statements
        --indentationLevel;
    }

    void enterElse_stmt(JavaParser::Else_stmtContext *ctx) override {

        enterElses(ctx);
    }

    void enterElses(antlr4::ParserRuleContext* ctx) {

        // find the first previous token in the same channel
        const auto stream = parser->getTokenStream();
        const auto channel = ctx->getStart()->getChannel();
        int pos = ctx->getStart()->getTokenIndex() - 1;
        while (pos > 0 && stream->get(pos)->getChannel() != channel) {
            --pos;
        }
        auto prevToken = stream->get(pos);

        // if the previous token is the end of a block, then no indentation
        if (prevToken->getType() == JavaParser::RCURLY) {
            return;
        }

        --indentationLevel;
        indent();
        ++indentationLevel;
    }

    void enterElse_if_stmt(JavaParser::Else_if_stmtContext* ctx) override { 

        enterElses(ctx);
    }

    void exitElse_if_stmt(JavaParser::Else_if_stmtContext * /*ctx*/) override {}

    void enterBlock_end(JavaParser::Block_endContext *ctx) override {
        --indentationLevel;
        indent();
    }

    void exitBlock_end(JavaParser::Block_endContext *ctx) override {
        ++indentationLevel;
    }

    void visitTerminal(antlr4::tree::TerminalNode *node) override {

        // Symbols with no space before them
        static const std::unordered_set<int> noBeforeSpace{
            JavaParser::RPAREN,         // ")"
            JavaParser::SEMICOLON,      // ";"
        };

        // Symbols with no space after them
        static const std::unordered_set<int> noAfterSpace{
            JavaParser::LPAREN,         // "("
            JavaParser::SEMICOLON,      // ";"
            JavaParser::LCURLY,         // "{"
        };

        // space before except for members of noBeforeSpace
        if (noBeforeSpace.find(node->getSymbol()->getType()) != noBeforeSpace.end()
            && pretty.back() == ' ')
            pretty.pop_back();

        pretty += node->getSymbol()->getText();
        
        // space after except for members of noAfterSpace
        if (noAfterSpace.find(node->getSymbol()->getType()) != noAfterSpace.end())
            return;
        pretty += " ";
    }

    void visitErrorNode(antlr4::tree::ErrorNode *node) override {}

    void enterEveryRule(antlr4::ParserRuleContext *ctx) override {}

    void exitEveryRule(antlr4::ParserRuleContext *ctx) override {}
};

#endif
