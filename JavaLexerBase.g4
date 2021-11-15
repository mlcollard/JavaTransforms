lexer grammar JavaLexerBase;

// Keywords
ABSTRACT : 'abstract';
CONTINUE : 'continue';
FOR : 'for';
NEW : 'new';
SWITCH : 'switch';
ASSERT : 'assert';
DEFAULT : 'default';
GOTO : 'goto';
PACKAGE : 'package';
SYNCHRONIZED : 'synchronized';
BOOLEAN : 'boolean';
DO : 'do';
IF : 'if';
PRIVATE : 'private';
//THIS : 'this';
BREAK : 'break';
//DOUBLE : 'double';
IMPLEMENTS : 'implements';
PROTECTED : 'protected';
THROW : 'throw';
//BYTE : 'byte';
ELSE : 'else';
IMPORT : 'import';
PUBLIC : 'public';
THROWS : 'throws';
CASE : 'case';
ENUM : 'enum';
INSTANCEOF : 'instanceof';
RETURN : 'return';
TRANSIENT : 'transient';
CATCH : 'catch';
EXTENDS : 'extends';
//INT : 'int';
//SHORT : 'short';
TRY : 'try';
//CHAR : 'char';
FINAL : 'final';
INTERFACE : 'interface';
STATIC : 'static';
//VOID : 'void';
CLASS : 'class';
FINALLY : 'finally';
//LONG : 'long';
STRICTFP : 'strictfp';
VOLATILE : 'volatile';
CONST : 'const';
//FLOAT : 'float';
NATIVE : 'native';
SUPER : 'super';
WHILE : 'while';

// Sections
LPAREN : '(' ;
RPAREN : ')' ;
LCURLY : '{' ;
RCURLY : '}' ;
LBRACKET : '[' ;
RBRACKET : ']' ;

SEMICOLON : ';' ;

NAME : [a-zA-Z_][a-zA-Z0-9_$]* ;

NUMBER : [0-9]+ ;

COMMENT : ('//' .*? ('\n')? | '/*' (. | '\n')*? '*/') -> channel(HIDDEN);

STRING : '\'' .*? '\'' | '"' .*? '"' | '\'\'\'' .*? '\'\'\'' | '"""' .*? '"""';

OPERATORS: '?' | '+' | '-' | '*' | '/' | '%' | '**' | '//' | '@' | '&' | '|' | '^' | '~' | '<<' | '>>' | '==' | '!=' |
           '>' | '<' | '>=' | '<=' | '=' | ':=' | '+=' | '-=' | '*=' | '/=' | '%=' | '**=' | '//=' | '@=' | '&=' |
           '|=' | '^=' | '<<=' | '>>=' | ':' | '->' | '.' | ',' | '!';

WS : (' ' | '\t' | '\n')+ -> channel(HIDDEN) ;

OTHER : .+?;
