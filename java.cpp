/*
    java.cpp

    A Java parser
*/

#include <iostream>
#include <fstream>
#include "JavaLexer.h"
#include "JavaParser.h"
#include "JavaTransform.hpp"
#include "JavaPrettyPrinter.hpp"

int indentationLevel = 1;

// indent according to the current indentation level
std::string indent() {
    std::string s = "\n";
    for (int i = 0; i < indentationLevel; ++i)
        s += "    ";

    return s;
}

void prettyPrint(antlr4::tree::ParseTree* tree, antlr4::Parser* parser) {

    antlr4::ParserRuleContext* rule = dynamic_cast<antlr4::ParserRuleContext*>(tree);
    if (rule) {

        // insert indentation at start
        switch (rule->getRuleIndex()) {
        case JavaParser::RuleNonblock:
            auto interval = rule->getSourceInterval();
            auto stream = dynamic_cast<antlr4::CommonTokenStream*>(parser->getTokenStream());

            auto factory = stream->getTokenSource()->getTokenFactory();
            auto newToken = factory->create(5, indent());
            antlr4::tree::TerminalNodeImpl*  terminalNode = new antlr4::tree::TerminalNodeImpl(newToken.release());

            rule->children.insert(rule->children.begin(), terminalNode);
            break;
        };

        // increase indentation for nested
        switch (rule->getRuleIndex()) {
        case JavaParser::RuleIf_stmt:
        case JavaParser::RuleWhile_stmt:
            ++indentationLevel;
        };

        // pretty print the children
        for (auto child : rule->children) {
            prettyPrint(child, parser);
        }

        if (rule->getRuleIndex() == JavaParser::RuleBlock_end) {
            --indentationLevel;
            auto interval = rule->getSourceInterval();
            auto stream = dynamic_cast<antlr4::CommonTokenStream*>(parser->getTokenStream());

            auto factory = stream->getTokenSource()->getTokenFactory();
            auto newToken = factory->create(5, indent());
            antlr4::tree::TerminalNodeImpl*  terminalNode = new antlr4::tree::TerminalNodeImpl(newToken.release());

            rule->children.insert(rule->children.begin(), terminalNode);
            ++indentationLevel;
        }

        // decrease indentation for nested
        switch (rule->getRuleIndex()) {
        case JavaParser::RuleIf_stmt:
        case JavaParser::RuleWhile_stmt:
            --indentationLevel;
        };

    } else {
        tree->getText();    
    }
}

int main(int argc, char* argv[]) {

    // setup input
    std::ifstream file(argv[1]);
    antlr4::ANTLRInputStream input(file);

    // setup lexer
    JavaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    JavaParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.main();
    parser.setTrace(false);

    // alter the tree with pretty print
    prettyPrint(tree, &parser);

    // output the parse tree
    std::cout << tree->getText() << '\n';

    return 0;
}
