%code requires{
	#include "Token.hpp"
	#include "Logger.hpp"
	extern int yylex();
	extern void yyerror(const char*, ...);
}

%union{
	IntegerLiteral intLit;
}

%token	<intLit>	IntegerLiteralToken

%start Screw
%%
Screw: IntegerLiteralToken {
		switch($1.intSize){
			case IntegerLiteral::Size::INT8: Logger::Log(Logger::Type::INFO, int($1.value.int8)); break;
			case IntegerLiteral::Size::INT16: Logger::Log(Logger::Type::INFO, $1.value.int16); break;
			case IntegerLiteral::Size::INT32: Logger::Log(Logger::Type::INFO, $1.value.int32); break;
			case IntegerLiteral::Size::INT64: Logger::Log(Logger::Type::INFO, $1.value.int64); break;
		}
	}


%%
