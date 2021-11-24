/*
    JavaTransform.hpp

    Application built on JavaListener.
*/

#ifndef INCLUDED_JAVATRANSFORM_HPP
#define INCLUDED_JAVATRANSFORM_HPP

#include "JavaListenerBlock.h"
#include <unordered_map>
#include <string>

class  JavaTransform : public JavaListener {
private:
    std::unordered_map<int, std::string> map{
        { JavaParser::RuleWhile_stmt, "while"},
        { JavaParser::RuleCondition, "condition"},
        { JavaParser::RuleName, "name"},
    };

public:

    virtual void enterMain(JavaParser::MainContext * /*ctx*/) {

        std::cout << R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<unit xmlns="https://mlcollard.net/mcollard">)";
    }
    
    virtual void exitMain(JavaParser::MainContext * /*ctx*/) {
        std::cout << "</unit>\n";
    }

    virtual void enterWhile_stmt(JavaParser::While_stmtContext *ctx) {
    }

    virtual void exitWhile_stmt(JavaParser::While_stmtContext *ctx) {
    }


    virtual void visitTerminal(antlr4::tree::TerminalNode *node) {

        std::cout << node->getSymbol()->getText();
    }

    virtual void visitErrorNode(antlr4::tree::ErrorNode *node) {}

    virtual void enterEveryRule(antlr4::ParserRuleContext *ctx) {

        auto it = map.find(ctx->getRuleIndex());
        if (it != map.end()) {
            std::cout << "<" << it->second << ">";
        }
    }

    virtual void exitEveryRule(antlr4::ParserRuleContext *ctx) {

        auto it = map.find(ctx->getRuleIndex());
        if (it != map.end()) {
            std::cout << "</" << it->second << ">";
        }

    }
};

#endif
