grammar Java;

options {
    language=Cpp;
    tokenVocab=JavaLexer;
}

main : (statement)* ;

statement : block | nonblock ;

nonblock : /* for_stmt | */ declaration | return_stmt | while_stmt | if_stmt /*| else_if_stmt | else_stmt */ | expr_stmt | do_stmt | break_stmt |
            continue_stmt | block | empty_stmt | goto_stmt | try_stmt | finally_stmt | synchronized_stmt ;

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
