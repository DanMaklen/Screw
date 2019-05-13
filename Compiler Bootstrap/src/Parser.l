%option noyywrap
%option nodefault
%option yylineno
%option batch

%{
	#define YY_DECL int yylex(AST*& ast)
%}

AllChar														[\f\v\r\n\t -~]
nAllChar													[^\f\v\r\n\t -~]

WS															[\f\v\r\n\t ]
nWS															[^\f\v\r\n\t ]
NL															[\r\f\v\n]
nNL															[^\f\v\r\n]

Lower														[a-z]
Upper														[A-Z]
Symbol														[!-/:-@[-`{-~]

BDigit														[0-1]
TDigit														[0-2]
ODigit														[0-7]
DDigit														[0-9]
HDigit														[0-9a-fA-F]

%%
	/*Arithmatic Operators*/
\+															{return PLUS;}
-															{return MINUS;}
\*															{return ASTERISK;}
\/															{return SLASH;}
%															{return PERCENT;}

	/*Logical Operators*/
not															{return NOT;}
and															{return AND;}
or															{return OR;}

	/*Comparison Operators*/
==															{return EQ;}
!=															{return NEQ;}
\<															{return LT;}
\<=															{return LTEQ;}
\>															{return GT;}
\>=															{return GTEQ;}

	/*Bitwise Operators*/
~															{return BITWISE_NOT;}
&															{return BITWISE_AND;}
\|															{return BITWISE_OR;}
\^															{return BITWISE_XOR;}
\<\<														{return SHIFT_LEFT;}
\>\>														{return SHIFT_RIGHT;}

	/*Assignment Operators*/
=															{return ASSIGN;}

	/*Punctuation*/
;															{return SEMICOLON;}
,															{return COMMA;}
\(															{return LEFT_PARENTHESIS;}
\)															{return RIGHT_PARENTHESIS;}
\{															{return LEFT_CURLY_BRACKET;}
\}															{return RIGHT_CURLY_BRACKET;}
\[															{return LEFT_SQUARE_BRACKET;}
\]															{return RIGHT_SQUARE_BRACKET;}

	/*Builtin Types*/
Integer|int													{return INT;}
Character|char												{return CHAR;}
Boolean|bool												{return BOOL;}
void														{return VOID;}

	/*Reserved Words*/
if															{return IF;}
else														{return ELSE;}
while														{return WHILE;}
class														{return CLASS;}
public														{return PUBLIC;}
protected													{return PROTECTED;}
private														{return PRIVATE;}

	/*Integer Literal*/
(0[bB]){BDigit}+(`{BDigit}+)*([su]?int(8|16|32|64)?)?		|
(0[tT]){TDigit}+(`{TDigit}+)*([su]?int(8|16|32|64)?)?		|
(0[oOcC]){ODigit}+(`{ODigit}+)*([su]?int(8|16|32|64)?)?		|
(0[dD])?{DDigit}+(`{DDigit}+)*([su]?int(8|16|32|64)?)?		|
(0[xXhH]){HDigit}+(`{HDigit}+)*([su]?int(8|16|32|64)?)?		{return INTEGER_LITERAL;}

	/*Boolean Literal*/
true														|
false														{return BOOLEAN_LITERAL;}

	/*Identifier*/
[_a-zA-Z][_@a-zA-Z0-9]*										{return IDENTIFIER;}

	/*Comments*/
"/?"{nWS}*						/*Word Comment*/			{}
"//"{nNL}*						/*Line Comment*/			{}
"/*"[/]*([^/]|[^*][/])*"*/"		/*Multi-Line Comment*/		{}

	/*WhiteSpace*/
{WS}+														{}

	/*Default Rule*/
.															{yyerror(ast, "Unrecognized character %c (%d).", *yytext, int(*yytext));}	//Default Rule
%%
