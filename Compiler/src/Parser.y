%param {AST*& ast}
%code requires{
	#include "Logger.hpp"
	#include "AST.hpp"
	using namespace std;
	extern int yylex(AST*&);
	extern void yyerror(AST*&, const char*, ...);
}
%define parse.error verbose
%union{
	const char* tokenString;
	AST* astNode;
}

%token 	PLUS MINUS ASTERISK SLASH PERCENT
%token	NOT AND OR
%token	EQ NEQ LT LTEQ GT GTEQ
%token	BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR SHIFT_LEFT SHIFT_RIGHT
%token	ASSIGN
%token	SEMICOLON COMMA
%token	LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%token	IF ELSE WHILE
%token	INT CHAR BOOL

%token	INTEGER_LITERAL BOOLEAN_LITERAL IDENTIFIER;

%start Screw
%%
Screw:
		StatementList{
			Logger::Log(Logger::Type::DEBUG, "Parsed Successfully!");
		}
	;
StatementList:
	|	StatementList Statement
	;
Statement:
		OpenStatement
	|	ClosedStatement
	;
OpenStatement:
		IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
	|	IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement ELSE OpenStatement
	|	WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS OpenStatement
	;
ClosedStatement:
		TerminalStatement
	|	IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement ELSE ClosedStatement
	|	WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement
	;
TerminalStatement:
		SEMICOLON
	|	ExpressionStatement
	|	VariableDeclarationStatement
	|	LEFT_CURLY_BRACKET StatementList RIGHT_CURLY_BRACKET
	;
VariableDeclarationStatement:
		TypeName Identifier SEMICOLON
	;
ExpressionStatement:
		Expression SEMICOLON
	;
TypeName:
		INT
	|	CHAR
	|	BOOL
	|	Identifier
	;
Expression:
		R0Expression
	;
R0Expression:
		R1Expression
	|	R0Expression ASSIGN R1Expression
	;
R1Expression:
		R2Expression
	|	R1Expression OR R2Expression
	;
R2Expression:
		R3Expression
	|	R2Expression AND R3Expression
	;
R3Expression:
		R4Expression
	|	NOT R4Expression
	;
R4Expression:
		R5Expression
	|	R4Expression EQ R5Expression
	|	R4Expression NEQ R5Expression
	|	R4Expression LT R5Expression
	|	R4Expression LTEQ R5Expression
	|	R4Expression GT R5Expression
	|	R4Expression GTEQ R5Expression
	;
R5Expression:
		R6Expression
	|	R5Expression PLUS R6Expression
	|	R5Expression MINUS R6Expression
	;
R6Expression:
		R7Expression
	|	R6Expression ASTERISK R7Expression
	|	R6Expression SLASH R7Expression
	|	R6Expression PERCENT R7Expression
	;
R7Expression:
		R8Expression
	|	R7Expression SHIFT_LEFT R8Expression
	|	R7Expression SHIFT_RIGHT R8Expression
	;
R8Expression:
		R9Expression
	|	R8Expression BITWISE_OR R9Expression
	;
R9Expression:
		R10Expression
	|	R9Expression BITWISE_XOR R10Expression
	;
R10Expression:
		R11Expression
	|	R10Expression BITWISE_AND R11Expression
	;
R11Expression:
		TerminalExpression
	|	PLUS TerminalExpression
	|	MINUS TerminalExpression
	|	BITWISE_NOT TerminalExpression
	;
TerminalExpression:
		INTEGER_LITERAL
	|	BOOLEAN_LITERAL
	|	Identifier
	|	LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
	|	FunctionCall
	;
FunctionCall:
		Identifier LEFT_PARENTHESIS ArgumentList RIGHT_PARENTHESIS
	;
ArgumentList:
		Argument
	|	ArgumentList COMMA Argument
	;
Argument:
		Expression
	;
Identifier:
		IDENTIFIER
	;
%%
