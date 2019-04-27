#include "Parser.hpp"
#include "Logger.hpp"
using namespace std;

extern int yyparse(AST*&);
extern void yyrestart(FILE*);

AST* Parser::Parse(const string& filePath){
	FILE* file = fopen(filePath.c_str(), "r");
	AST* ast = nullptr;
	yyrestart(file);
	if(yyparse(ast) != 0)
		return nullptr;
	fclose(file);
	return ast;
}
