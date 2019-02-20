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

%token 					PLUS MINUS ASTERISK SLASH PERCENT
%token					NOT AND OR
%token					EQ NEQ LT LTEQ GT GTEQ
%token					BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR SHIFT_LEFT SHIFT_RIGHT
%token					ASSIGN
%token					SEMICOLON COMMA
%token					LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%token					IF ELSE WHILE
%token					INT CHAR BOOL

%token	<tokenString>	INTEGER_LITERAL BOOLEAN_LITERAL IDENTIFIER;

%type	<astNode>		StatementList Statement
%type	<astNode>		OpenStatement ClosedStatement
%type	<astNode>		R0Expression R1Expression R2Expression R3Expression R4Expression
%type	<astNode>		R5Expression R6Expression R7Expression R8Expression R9Expression
%type	<astNode>		R10Expression R11Expression
%type	<astNode>		TerminalStatement TerminalExpression
%type	<astNode>		Identifier Expression TypeName
%type	<astNode>		ExpressionStatement VariableDeclarationStatement

%start Screw
%%
Screw:
		StatementList{
			ast = $1;
		}
	;
StatementList:
		{
			$$ = new ASTList(ASTList::Type::STATEMENT_LIST);
		}
	|	StatementList Statement{
			if($2 != nullptr) dynamic_cast<ASTList*>($1)->Append($2);
			$$ = $1;
		}
	;
Statement:
		OpenStatement{
			$$ = $1;
		}
	|	ClosedStatement{
			$$ = $1;
		}
	;
OpenStatement:
		IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement{
			$$ = new If($3, $5);
		}
	|	IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement ELSE OpenStatement{
			$$ = new If($3, $5, $7);
		}
	|	WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS OpenStatement{
			$$ = new While($3, $5);
		}
	;
ClosedStatement:
		TerminalStatement{
			$$ = $1;
		}
	|	IF LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement ELSE ClosedStatement{
			$$ = new If($3, $5, $7);
		}
	|	WHILE LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS ClosedStatement{
			$$ = new While($3, $5);
		}
	;
TerminalStatement:
		SEMICOLON {
			$$ = (AST*)nullptr;
		}
	|	ExpressionStatement{
			$$ = $1;
		}
	|	VariableDeclarationStatement{
			$$ = $1;
		}
	|	LEFT_CURLY_BRACKET StatementList RIGHT_CURLY_BRACKET{
			$$ = $2;
		}
	;
VariableDeclarationStatement:
		TypeName Identifier SEMICOLON{
			$$ = new VariableDeclaration($1, $2);
		}
	;
ExpressionStatement:
		Expression SEMICOLON{
			$$ = $1;
		}
	;
TypeName:
		INT{
			$$ = new TypeName(TypeName::Type::INTEGER);
		}
	|	CHAR{
			$$ = new TypeName(TypeName::Type::CHARACTER);
		}
	|	BOOL{
			$$ = new TypeName(TypeName::Type::BOOLEAN);
		}
	|	Identifier{
			$$ = new TypeName($1);
		}
	;
Expression:
		R0Expression{
			$$ = $1;
		}
	;
R0Expression:
		R1Expression{
			$$ = $1;
		}
	|	R0Expression ASSIGN R1Expression{
			$$ = new Expression(Expression::ASSIGNMENT, $1, $3);
		}
	;
R1Expression:
		R2Expression{
			$$ = $1;
		}
	|	R1Expression OR R2Expression{
			$$ = new Expression(Expression::LOGICAL_OR, $1, $3);
		}
	;
R2Expression:
		R3Expression{
			$$ = $1;
		}
	|	R2Expression AND R3Expression{
			$$ = new Expression(Expression::LOGICAL_AND, $1, $3);
		}
	;
R3Expression:
		R4Expression{
			$$ = $1;
		}
	|	NOT R4Expression{
			$$ = new Expression(Expression::LOGICAL_NOT, $2);
		}
	;
R4Expression:
		R5Expression{
			$$ = $1;
		}
	|	R4Expression EQ R5Expression{
			$$ = new Expression(Expression::EQ, $1, $3);
		}
	|	R4Expression NEQ R5Expression{
			$$ = new Expression(Expression::NEQ, $1, $3);
		}
	|	R4Expression LT R5Expression{
			$$ = new Expression(Expression::LT, $1, $3);
		}
	|	R4Expression LTEQ R5Expression{
			$$ = new Expression(Expression::LTEQ, $1, $3);
		}
	|	R4Expression GT R5Expression{
			$$ = new Expression(Expression::GT, $1, $3);
		}
	|	R4Expression GTEQ R5Expression{
			$$ = new Expression(Expression::GTEQ, $1, $3);
		}
	;
R5Expression:
		R6Expression{
			$$ = $1;
		}
	|	R5Expression PLUS R6Expression{
			$$ = new Expression(Expression::ADDITION, $1, $3);
		}
	|	R5Expression MINUS R6Expression{
			$$ = new Expression(Expression::SUBTRACTION, $1, $3);
		}
	;
R6Expression:
		R7Expression{
			$$ = $1;
		}
	|	R6Expression ASTERISK R7Expression{
			$$ = new Expression(Expression::MULTIPLICATION, $1, $3);
		}
	|	R6Expression SLASH R7Expression{
			$$ = new Expression(Expression::DIVISION, $1, $3);
		}
	|	R6Expression PERCENT R7Expression{
			$$ = new Expression(Expression::REMAINDER, $1, $3);
		}
	;
R7Expression:
		R8Expression{
			$$ = $1;
		}
	|	R7Expression SHIFT_LEFT R8Expression{
			$$ = new Expression(Expression::SHIFT_LEFT, $1, $3);
		}
	|	R7Expression SHIFT_RIGHT R8Expression{
			$$ = new Expression(Expression::SHIFT_RIGHT, $1, $3);
		}
	;
R8Expression:
		R9Expression{
			$$ = $1;
		}
	|	R8Expression BITWISE_OR R9Expression{
			$$ = new Expression(Expression::BITWISE_OR, $1, $3);
		}
	;
R9Expression:
		R10Expression{
			$$ = $1;
		}
	|	R9Expression BITWISE_XOR R10Expression{
			$$ = new Expression(Expression::BITWISE_XOR, $1, $3);
		}
	;
R10Expression:
		R11Expression{
			$$ = $1;
		}
	|	R10Expression BITWISE_AND R11Expression{
			$$ = new Expression(Expression::BITWISE_AND, $1, $3);
		}
	;
R11Expression:
		TerminalExpression{
			$$ = $1;
		}
	|	PLUS TerminalExpression{
			$$ = new Expression(Expression::POSITIVE, $2);
		}
	|	MINUS TerminalExpression{
			$$ = new Expression(Expression::NEGATIVE, $2);
		}
	|	BITWISE_NOT TerminalExpression{
			$$ = new Expression(Expression::BITWISE_NOT, $2);
		}
	;
TerminalExpression:
		INTEGER_LITERAL{
			$$ = new IntegerLiteral($1);
		}
	|	BOOLEAN_LITERAL{
			$$ = new BooleanLiteral($1);
		}
	|	Identifier {
			$$ = $1;
		}
	|	LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS{
			$$ = $2;
		}
	;
Identifier:
		IDENTIFIER	{
			$$ = new Identifier($1);
		}
	;
%%
