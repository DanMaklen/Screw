#include "Logger.hpp"
#include "Parser.hpp"
#include "AST.hpp"

long long eval(const AST* ast){
	switch(ast->GetASTNodeType()){
	case ASTNodeType::EXPRESSION:{
		const Expression* expr = dynamic_cast<const Expression*>(ast);
		switch(expr->GetOperation()){
		case Expression::Operation::ADDITION:
			return eval(ast->GetChildren()[0]) + eval(ast->GetChildren()[1]);
		case Expression::Operation::SUBTRACTION:
			return eval(ast->GetChildren()[0]) - eval(ast->GetChildren()[1]);
		case Expression::Operation::MULTIPLICATION:
			Logger::Log(Logger::Type::INFO, eval(ast->GetChildren()[1]));
			return eval(ast->GetChildren()[0]) * eval(ast->GetChildren()[1]);
		case Expression::Operation::DIVISION:
			return eval(ast->GetChildren()[0]) / eval(ast->GetChildren()[1]);
		case Expression::Operation::REMAINDER:
			return eval(ast->GetChildren()[0]) % eval(ast->GetChildren()[1]);
		}
	}
	case ASTNodeType::INTEGER_LITERAL:{
		const IntegerLiteral* val = dynamic_cast<const IntegerLiteral*>(ast);
		return val->value.int64;
	}
	}
	return 0;
}

int main(int argc, const char * argv[]){
	// TODO: Rewrite argument parser
	if(argc < 2){
		Logger::Log(Logger::Type::INFO, "No input file");
		return 0;
	}
	Parser parser;

	AST* ast;
	ast = parser.Parse(argv[1]);
	Logger::Debug(eval(ast));
	return 0;
}
