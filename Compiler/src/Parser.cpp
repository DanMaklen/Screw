#include "Parser.hpp"
using namespace std;

extern int yyparse();
extern void yyrestart(FILE*);

void Parser::Parse(const string& filePath){
	FILE* file = fopen(filePath.c_str(), "r");
	yyrestart(file);
	yyparse();
	fclose(file);
}
