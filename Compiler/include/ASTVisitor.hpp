#pragma once
#include "AST.hpp"

class ASTVisitor{
private:
	virtual void ProcessExpression(const Expression* ast);
	virtual void ProcessTerminalValue(const TerminalValue* ast);
protected:
	void Dispatch(AST* ast);
public:
	ASTVisitor() = default;
	ASTVisitor(const ASTVisitor&) = default;
	ASTVisitor(ASTVisitor&&) = default;
	
	virtual void Visit(AST* ast) = 0;
};

class ASTVisitor_BFS : ASTVisitor{
public:
	virtual void Visit(AST* ast);
};

class ASTVisitor_DFS : ASTVisitor{
public:
	virtual void Visit(AST* ast);
};
