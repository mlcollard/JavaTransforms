/*
    JavaPrettyPrinter.hpp

    Application built on JavaListener.
*/

#ifndef INCLUDED_JAVAPRETTYPRINTER_HPP
#define INCLUDED_JAVAPRETTYPRINTER_HPP

#include "JavaListenerBlock.h"
#include <unordered_map>
#include <string>

class  JavaPrettyPrinter : public JavaListener {
private:

    // pretty form of code
    std::string pretty;

    // level of indent
    int indentationLevel = 1;

    // indentation string
    std::string indentation = "    ";

public:

    virtual void enterMain(JavaParser::MainContext *ctx) override {
    }

    virtual void exitMain(JavaParser::MainContext *ctx) override {
        std::cout << pretty;
    }

    void newline() {
        pretty += "\n";
    }

    // indent according to the current indentation level
    void indent() {

        newline();
        for (int i = 0; i < indentationLevel; ++i)
            pretty += indentation;
    }

    virtual void enterStatement(JavaParser::StatementContext * ctx) override {
    }

    virtual void exitStatement(JavaParser::StatementContext * /*ctx*/) override {
    }

    virtual void enterElse_stmt(JavaParser::Else_stmtContext *ctx) override {
    }

    virtual void enterBlock(JavaParser::BlockContext *ctx) override {
    }

    virtual void exitBlock(JavaParser::BlockContext *ctx) override {
    }

    virtual void visitTerminal(antlr4::tree::TerminalNode *node) override {

        pretty += node->getSymbol()->getText();
        pretty += " ";
    }

    virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override {}

    virtual void enterEveryRule(antlr4::ParserRuleContext *ctx) override {}

    virtual void exitEveryRule(antlr4::ParserRuleContext *ctx) override {}
};

#endif
