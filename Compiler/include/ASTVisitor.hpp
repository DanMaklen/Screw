#pragma once
#include "AST.hpp"

class ASTVisitor{
private:
	virtual void ProcessExpression(const Expression* ast);
	virtual void ProcessIntegerLiteral(const IntegerLiteral* ast);
	virtual void ProcessBooleanLiteral(const BooleanLiteral* ast);
	virtual void ProcessIdentifier(const Identifier* ast);
	virtual void ProcessStatementList(const StatementList* ast);
	virtual void ProcessIfStatement(const IfStatement* ast);
	virtual void ProcessWhileStatement(const WhileStatement* ast);
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
