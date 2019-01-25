%param {AST*& ast}
%code requires{
	#include "Token.hpp"
	#include "Logger.hpp"
	#include "AST.hpp"
	extern int yylex(AST*&);
	extern void yyerror(AST*&, const char*, ...);
}

%union{
	IntegerLiteral intLiteral;
	AST* astNode;
}

%token 					PLUS HYPHEN_MINUS
%token					ASTERISK SLASH PERCENT_SIGN
%token					SEMICOLON

%token	<intLiteral>	INTEGER_LITERAL

%type	<astNode>		Expression
%type	<astNode>		Rank0Expression Rank1Expression Rank2Expression
%type	<astNode>		TerminalValue Screw

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
		TerminalValue{
			$$ = $1;
		}
	;
TerminalValue:
		INTEGER_LITERAL{
			$$ = new TerminalValue($1);
		}
	;
%%
