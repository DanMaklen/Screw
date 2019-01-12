#include "Logger.hpp"
#include "Parser.hpp"

int main(int argc, const char * argv[]){
	// TODO: Rewrite argument parser
	if(argc < 2){
		Logger::Log(Logger::Type::INFO, "No input file");
		return 0;
	}
	Parser parser;
	parser.Parse(argv[1]);
	return 0;
}
