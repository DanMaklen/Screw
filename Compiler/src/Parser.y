%param {AST*& ast}
%code requires{
	#include "Logger.hpp"
	#include "AST.hpp"
	#include <string>
	using namespace std;
	extern int yylex(AST*&);
	extern void yyerror(AST*&, const char*, ...);
}

%union{
	const char* tokenString;
	AST* astNode;
}

%token 					PLUS HYPHEN_MINUS ASTERISK SLASH PERCENT_SIGN
%token					SEMICOLON LEFT_PARENTHESIS RIGHT_PARENTHESIS

%token	<tokenString>	INTEGER_LITERAL

%type	<astNode>		Expression
%type	<astNode>		Rank0Expression Rank1Expression Rank2Expression

%start Screw
%%
Screw:
		Expression{
			ast = $1;
		}
	;
Expression:
		Rank0Expression{
			$$ = $1;
		}
	;
Rank0Expression:
		Rank1Expression{
			$$ = $1;
		}
	|	Rank0Expression PLUS Rank1Expression{
			$$ = new Expression(Expression::ADDITION, $1, $3);
		}
	|	Rank0Expression HYPHEN_MINUS Rank1Expression{
			$$ = new Expression(Expression::SUBTRACTION, $1, $3);
		}
	;
Rank1Expression:
		Rank2Expression{
			$$ = $1;
		}
	|	Rank1Expression ASTERISK Rank2Expression{
			$$ = new Expression(Expression::MULTIPLICATION, $1, $3);
		}
	|	Rank1Expression SLASH Rank2Expression{
			$$ = new Expression(Expression::DIVISION, $1, $3);
		}
	|	Rank1Expression PERCENT_SIGN Rank2Expression{
			$$ = new Expression(Expression::REMAINDER, $1, $3);
		}
	;
Rank2Expression:
		INTEGER_LITERAL{
			$$ = new IntegerLiteral($1);
		}
	|	LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS{
			$$ = $2;
		}
	;
%%
