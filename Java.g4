grammar Java;

options {
    language=Cpp;
    tokenVocab=JavaLexer;
}

main : (statement)* ;

statement : block #noindent | /* for_stmt #nonnested| */ declaration #nonnested| return_stmt #nonnested| while_stmt #nested| if_stmt /*| else_if_stmt #nonnested| else_stmt */ #nested| expr_stmt #nonnested| do_stmt #nested| break_stmt #nonnested|
            continue_stmt #nonnested| empty_stmt #nonnested| goto_stmt #nonnested| try_stmt #nonnested| finally_stmt #nonnested| synchronized_stmt #nonnested;

declaration : /* class_decl | */ function | function_decl | import_stmt | package_stmt | static_block | specifier ;

function_header : (STATIC | CONST)* (name)+ LPAREN (expr | COMMA)* RPAREN ;

function : function_header block ;

function_decl : function_header stmt_end ;

static_block : STATIC block ;

constructor : name LPAREN (expr | COMMA)* RPAREN (THROWS name)? block ;

specifier : FINAL | SYNCHRONIZED | ABSTRACT | NATIVE | STRICTFP | TRANSIENT | PUBLIC | PRIVATE | PROTECTED ;

synchronized_stmt : SYNCHRONIZED LPAREN name RPAREN block ;

goto_stmt : GOTO (NAME | CASE (expr)*)? ;

return_stmt : RETURN (expr)* stmt_end ;

package_stmt : PACKAGE name stmt_end ;

import_stmt : IMPORT name (ASTERISK)? stmt_end ;

continue_stmt : CONTINUE (expr)* stmt_end ;

break_stmt : BREAK (expr)* stmt_end ;

empty_stmt : stmt_end ;

stmt_end : SEMICOLON ;

while_stmt : WHILE condition statement ;

condition: LPAREN (expr)* RPAREN ;

if_stmt : IF LPAREN (expr)* RPAREN statement (else_if_stmt)* (else_stmt)*;

else_stmt : ELSE statement ;

else_if_stmt : ELSE IF condition statement ;

expr_stmt : expr stmt_end ;

name : NAME (DOT NAME)* (DOT)? ;

call : name LPAREN (expr | COMMA)? RPAREN ;

block : LCURLY (statement)* block_end ;

block_end : RCURLY ;

expr : (name | NUMBER | STRING | operators | call | LPAREN (expr)* RPAREN)+ ;

operators : OPERATORS | COMMA | NEW ;

try_stmt : TRY (LPAREN (expr | SEMICOLON)* RPAREN)? block ;

catch_stmt : CATCH (LPAREN (expr)* RPAREN)? block ;

finally_stmt : FINALLY (LPAREN (expr)* RPAREN)? block ;

do_stmt : DO statement WHILE LPAREN (expr)? RPAREN stmt_end ;
