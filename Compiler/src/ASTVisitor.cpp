#include "ASTVisitor.hpp"
#include "Logger.hpp"
#include <queue>
using namespace std;

void ASTVisitor::ProcessExpression(const Expression* ast){}
void ASTVisitor::ProcessIntegerLiteral(const IntegerLiteral* ast){}
void ASTVisitor::ProcessBooleanLiteral(const BooleanLiteral* ast){}
void ASTVisitor::ProcessIdentifier(const Identifier* ast){}
void ASTVisitor::Dispatch(AST* ast){
	switch(ast->GetASTNodeType()){
		case ASTNodeType::EXPRESSION: this->ProcessExpression(dynamic_cast<Expression*>(ast)); break;
		case ASTNodeType::INTEGER_LITERAL: this->ProcessIntegerLiteral(dynamic_cast<IntegerLiteral*>(ast)); break;
		case ASTNodeType::BOOLEAN_LITERAL: this->ProcessBooleanLiteral(dynamic_cast<BooleanLiteral*>(ast)); break;
		case ASTNodeType::IDENTIFIER: this->ProcessIdentifier(dynamic_cast<Identifier*>(ast)); break;
		default: Logger::Log(Logger::Type::ERROR, "Unknown ASTNodeType ", ast->GetASTNodeType());
	}
}

void ASTVisitor_BFS::Visit(AST* ast){
	queue<AST*> Q;
	Q.push(ast);

	while(!Q.empty()){
		AST* cur = Q.front(); Q.pop();
		this->Dispatch(cur);
		for(AST* child : cur->GetChildren())
			Q.push(child);
	}
}
void ASTVisitor_DFS::Visit(AST* ast){
	this->Dispatch(ast);
	for(AST* child : ast->GetChildren())
		this->Visit(child);
}
