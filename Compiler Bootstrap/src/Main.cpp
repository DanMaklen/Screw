#include "Logger.hpp"
#include "Parser.hpp"
#include "AST.hpp"
#include "ASTFileWriter.hpp"
#include "Tester.hpp"

int main(int argc, const char * argv[]){
	Tester tester("UnitTests/Parser");
	Tester::TestResultSummary results = tester.Run();
	Logger::Log(Logger::Type::INFO, "PassRate:", results.passRate);

	for(Tester::TestResult result : results.failures){
		Logger::Log(Logger::Type::INFO, result.filePath, " ", result.Expected, " ", result.Result);
	}

	// TODO: Rewrite argument parser
	// if(argc < 2){
	// 	Logger::Log(Logger::Type::INFO, "No input file");
	// 	return 0;
	// }
	// Parser parser;
	//
	// AST* ast;
	// ast = parser.Parse(argv[1]);
	// ASTFileWriter astFile("./out/test.ast");
	// astFile.WriteAST(ast);
	return 0;
}
