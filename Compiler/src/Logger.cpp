#include "Logger.hpp"
#include <iostream>
#include <cstdio>
#include <cstdarg>
using namespace std;

extern int yylineno;
void yyerror(const char* s, ...){
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
		default: return "::";
	}
}
