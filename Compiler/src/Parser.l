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
[+]															{return PLUS;}
[-]															{return HYPHEN_MINUS;}
[*]															{return ASTERISK;}
[/]															{return SLASH;}
[%]															{return PERCENT_SIGN;}

	/*Punctuation*/
[;]															{return SEMICOLON;}
[(]															{return LEFT_PARENTHESIS;}
[)]															{return RIGHT_PARENTHESIS;}

	/*Integer Literal*/
(0[bB]){BDigit}+(`{BDigit}+)*((s|u)?int(8|16|32|64)?)?		|
(0[tT]){TDigit}+(`{TDigit}+)*((s|u)?int(8|16|32|64)?)?		|
(0[oOcC]){ODigit}+(`{ODigit}+)*((s|u)?int(8|16|32|64)?)?	|
(0[dD])?{DDigit}+(`{DDigit}+)*((s|u)?int(8|16|32|64)?)?		|
(0[xXhH]){HDigit}+(`{HDigit}+)*((s|u)?int(8|16|32|64)?)?	{yylval.tokenString = yytext; return INTEGER_LITERAL;}

"/?"{nWS}*						/*Word Comment*/			{}
"//"{nNL}*						/*Line Comment*/			{}
"/*"[/]*([^/]|[^*][/])*"*/"		/*Multi-Line Comment*/		{}

	/*WhiteSpace*/
{WS}+														{}

	/*Default Rule*/
.															{yyerror(ast, "Unrecognized character %c (%d).", *yytext, int(*yytext));}	//Default Rule
%%
