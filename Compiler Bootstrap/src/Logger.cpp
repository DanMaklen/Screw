#include "Logger.hpp"
#include <cstdio>
#include <cstdarg>
#include "AST.hpp"
using namespace std;

extern int yylineno;
void yyerror(AST*& ast, const char* s, ...){
	printf("Line %d: ", yylineno);
	va_list ap;
	va_start(ap, s);
	vprintf(s, ap);
	printf("\n");
}

string Logger::MessageHeader(Type type){
	switch(type){
		case Type::ERROR: return "ERROR::";
		case Type::WARNING: return "WARNING::";
		case Type::INFO: return "INFO::";
		case Type::DEBUG: return "DEBUG::";
		default: return "::";
	}
}
