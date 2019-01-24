#pragma once
#include "AST.hpp"

class ASTVisitor{
private:
	virtual void ProcessExpression(const AST* ast);
	virtual void ProcessTerminalValue(const AST* ast);
protected:
	void Dispatch(AST* ast);
public:
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
