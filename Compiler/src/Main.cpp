#include "Logger.hpp"
#include "Parser.hpp"
#include "AST.hpp"
#include "ASTFileWriter.hpp"

int main(int argc, const char * argv[]){
	// TODO: Rewrite argument parser
	if(argc < 2){
		Logger::Log(Logger::Type::INFO, "No input file");
		return 0;
	}
	Parser parser;

	AST* ast;
	ast = parser.Parse(argv[1]);
	ASTFileWriter astFile("./out/test.ast");
	astFile.WriteAST(ast);
	return 0;
}
