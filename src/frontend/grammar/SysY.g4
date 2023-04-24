grammar SysY;
options{
    language=Cpp;
}
compUnit: (varDecl | constDecl | funcDef)+;

constDecl: ConstPrefix bType def ( ',' def)* ';';
varDecl:  bType def ( ',' def)* ';';

funcDef: funcType Ident '('(params+=funcFParam (',' params+=funcFParam)*)?')' block;
funcType: VoidType | IntType | FloatType;
bType: IntType | FloatType;

def: Ident (arrAccess)* ( '=' initVal)?;
funcFParam: bType Ident ('['']' (arrAccess)*)?;
block: '{' (varDecl | constDecl | stmt)* '}';
stmt: lVal '=' exp ';' # assignStmt
    | (exp)? ';' # expStmt
    | block # blockStmt
    | IF '(' cond ')' stmt (ELSE stmt)? # condStmt
    | WHILE '(' cond ')' stmt # loopStmt
    | BREAK ';' # breakStmt
    | CONTINUE ';' # contStmt
    | RETURN (exp)? ';' # returnStmt
    ;

initVal: exp
        |'{' initVal (',' initVal)* '}'
        ;
cond:exp
    |cond comp=('<'|'>'|'<='|'>=') cond
    |cond comp=('=='|'!=') cond
    |cond comp='&&' cond
    |cond comp='||' cond
    ;

exp: IntConstant
    | FloatConstant
    | lVal
    | Ident '(' (exp (',' exp)* )? ')'
    | '(' exp ')'
    | op=('+'|'-'| '!') exp
    | exp op=('*' | '/' | '%') exp
    | exp op=('+' | '-') exp
    ;


lVal: Ident (arrAccess)*;
arrAccess: '[' exp ']';


WS: [ \t\r\n]+->channel(HIDDEN);
COMMENT:('//' ~[\r\n]* 
        | '/*' .*? '*/')->skip
        ;
VoidType: 'void';
IntType:'int';
FloatType: 'float';
ConstPrefix: 'const';
IF: 'if';
ELSE: 'else';
WHILE: 'while';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

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
