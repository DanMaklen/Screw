%param {AST*& ast}
%code requires{
	#include "Logger.hpp"
	#include "AST.hpp"
	using namespace std;
	extern int yylex(AST*&);
	extern void yyerror(AST*&, const char*, ...);
}

%union{
	const char* tokenString;
	AST* astNode;
}

%token 					PLUS MINUS ASTERISK SLASH PERCENT
%token					NOT AND OR
%token					EQ NEQ LT LTEQ GT GTEQ
%token					BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR SHIFT_LEFT SHIFT_RIGHT
%token					SEMICOLON LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token					IF WHILE

%token	<tokenString>	INTEGER_LITERAL BOOLEAN_LITERAL IDENTIFIER;

%type	<astNode>		Expression
%type	<astNode>		R0Expression R1Expression R2Expression R3Expression R4Expression
%type	<astNode>		R5Expression R6Expression R7Expression R8Expression R9Expression
%type	<astNode>		R10Expression
%type	<astNode>		TerminalExpression

%start Screw
%%
Screw:
		Expression{
			ast = $1;
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
	|	R0Expression OR R1Expression{
			$$ = new Expression(Expression::LOGICAL_OR, $1, $3);
		}
	;
R1Expression:
		R2Expression{
			$$ = $1;
		}
	|	R1Expression AND R2Expression{
			$$ = new Expression(Expression::LOGICAL_AND, $1, $3);
		}
	;
R2Expression:
		R3Expression{
			$$ = $1;
		}
	|	NOT R3Expression{
			$$ = new Expression(Expression::LOGICAL_NOT, $2);
		}
	;
R3Expression:
		R4Expression{
			$$ = $1;
		}
	|	R3Expression EQ R4Expression{
			$$ = new Expression(Expression::EQ, $1, $3);
		}
	|	R3Expression NEQ R4Expression{
			$$ = new Expression(Expression::NEQ, $1, $3);
		}
	|	R3Expression LT R4Expression{
			$$ = new Expression(Expression::LT, $1, $3);
		}
	|	R3Expression LTEQ R4Expression{
			$$ = new Expression(Expression::LTEQ, $1, $3);
		}
	|	R3Expression GT R4Expression{
			$$ = new Expression(Expression::GT, $1, $3);
		}
	|	R3Expression GTEQ R4Expression{
			$$ = new Expression(Expression::GTEQ, $1, $3);
		}
	;
R4Expression:
		R5Expression{
			$$ = $1;
		}
	|	R4Expression PLUS R5Expression{
			$$ = new Expression(Expression::ADDITION, $1, $3);
		}
	|	R4Expression MINUS R5Expression{
			$$ = new Expression(Expression::SUBTRACTION, $1, $3);
		}
	;
R5Expression:
		R6Expression{
			$$ = $1;
		}
	|	R5Expression ASTERISK R6Expression{
			$$ = new Expression(Expression::MULTIPLICATION, $1, $3);
		}
	|	R5Expression SLASH R6Expression{
			$$ = new Expression(Expression::DIVISION, $1, $3);
		}
	|	R5Expression PERCENT R6Expression{
			$$ = new Expression(Expression::REMAINDER, $1, $3);
		}
	;
R6Expression:
		R7Expression{
			$$ = $1;
		}
	|	R6Expression SHIFT_LEFT R7Expression{
			$$ = new Expression(Expression::SHIFT_LEFT, $1, $3);
		}
	|	R6Expression SHIFT_RIGHT R7Expression{
			$$ = new Expression(Expression::SHIFT_RIGHT, $1, $3);
		}
	;
R7Expression:
		R8Expression{
			$$ = $1;
		}
	|	R7Expression BITWISE_OR R8Expression{
			$$ = new Expression(Expression::BITWISE_OR, $1, $3);
		}
	;
R8Expression:
		R9Expression{
			$$ = $1;
		}
	|	R8Expression BITWISE_XOR R9Expression{
			$$ = new Expression(Expression::BITWISE_XOR, $1, $3);
		}
	;
R9Expression:
		R10Expression{
			$$ = $1;
		}
	|	R9Expression BITWISE_AND R10Expression{
			$$ = new Expression(Expression::BITWISE_AND, $1, $3);
		}
	;
R10Expression:
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
	|	IDENTIFIER {
			$$ = new Identifier($1);
		}
	|	LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS{
			$$ = $2;
		}
	;
%%
