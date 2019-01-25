#include "ASTVisitor.hpp"
#include "Logger.hpp"
#include <queue>
using namespace std;

void ASTVisitor::ProcessExpression(const Expression* ast){}
void ASTVisitor::ProcessTerminalValue(const TerminalValue* ast){}
void ASTVisitor::Dispatch(AST* ast){
	switch(ast->GetASTNodeType()){
	case ASTNodeType::EXPRESSION: this->ProcessExpression(dynamic_cast<Expression*>(ast)); break;
	case ASTNodeType::TERMINAL_VALUE: this->ProcessTerminalValue(dynamic_cast<TerminalValue*>(ast)); break;
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
