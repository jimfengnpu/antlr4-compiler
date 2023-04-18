grammar SysY;
options{
    language=Cpp;
}
compUnit: (decl)+;

decl: (comDecl);

comDecl:  bType comDef ( ',' comDef)* ';';
bType: 'int' | 'float';
comDef: Ident ('[' exp ']')* ( '=' initVal);

initVal: exp
        |'{' initVal (',' initVal)* '}'
        ;
exp: mulExp (('+'|'-') mulExp)*;
mulExp: unaryExp (('*'| '/' | '%') unaryExp)*;
unaryExp: priExp;
priExp: '(' exp ')'
        | lVal
        | IntConstant 
        | FloatConstant
        ;
lVal: Ident ('[' exp ']')*;



WS: [ \t\r\n]+->channel(HIDDEN);
COMMENT:('//' ~[\r\n]* 
        | '/*' .*? '*/')->skip
        ;
IntConstant: NonZeroDigit Digit*
            | '0' OctalDigit*
            | '0' [xX] HexadecimalDigit+;
FloatConstant
    :   DecimalFloatingConstant
    |   HexadecimalFloatingConstant
    ;
fragment DecimalFloatingConstant
    :   FractionalConstant ExponentPart? 
    |   DigitSequence ExponentPart
    ;

fragment HexadecimalFloatingConstant
    :   '0'[xX] (HexadecimalFractionalConstant | HexadecimalDigits) BinaryExponentPart
    ;

fragment FractionalConstant
    :   DigitSequence? '.' DigitSequence
    |   DigitSequence '.'
    ;

fragment ExponentPart:   [eE] Sign? DigitSequence;
fragment Sign:   [+-];

DigitSequence:   Digit+;

fragment HexadecimalFractionalConstant
    :   HexadecimalDigits? '.' HexadecimalDigits
    |   HexadecimalDigits '.';
fragment BinaryExponentPart:   [pP] Sign? DigitSequence;
fragment HexadecimalDigits:   HexadecimalDigit+;

Ident:NonDigit (NonDigit | Digit)*;
fragment NonDigit: [a-zA-Z_];
fragment Digit: [0-9];
fragment NonZeroDigit: [1-9];
fragment OctalDigit: [0-7];
fragment HexadecimalDigit: [0-9a-fA-F];
