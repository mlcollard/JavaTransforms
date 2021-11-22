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

    antlr4::tree::ParseTreeWalker walker;
    JavaPrettyPrinter transform;
    walker.walk(&transform, tree);

    return 0;
}
