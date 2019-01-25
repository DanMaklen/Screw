#include "Parser.hpp"
using namespace std;

extern int yyparse(AST*&);
extern void yyrestart(FILE*);

AST* Parser::Parse(const string& filePath){
	FILE* file = fopen(filePath.c_str(), "r");
	AST* ast;
	yyrestart(file);
	yyparse(ast);
	fclose(file);
	return ast;
}
