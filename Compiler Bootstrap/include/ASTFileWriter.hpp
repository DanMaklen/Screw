#pragma once

#include "ASTVisitor.hpp"
#include "AST.hpp"
#include <fstream>
#include <string>

class ASTFileWriter : public ASTVisitor{
	ASTFileWriter() = delete;
	ASTFileWriter(const ASTFileWriter&) = delete;
private:
	std::ofstream astFile;
private:
	static std::string GetString_ASTNodeType(ASTNodeType astNodeType);
	static std::string GetString_ASTListType(ASTList::Type listType);
	static std::string GetString_TypeNameType(TypeName::Type typeNameType);
	static std::string GetString_ExpressionOperation(Expression::Operation operation);
	static std::string GetString_IntegerLiteralSize(IntegerLiteral::Size size);
	static std::string GetString_Boolean(bool boolean);

	virtual void ProcessExpression(const Expression* ast);
	virtual void ProcessIntegerLiteral(const IntegerLiteral* ast);
	virtual void ProcessBooleanLiteral(const BooleanLiteral* ast);
	virtual void ProcessIdentifier(const Identifier* ast);
	virtual void ProcessASTList(const ASTList* ast);
	virtual void ProcessIf(const If* ast);
	virtual void ProcessWhile(const While* ast);
	virtual void ProcessVariableDeclaration(const VariableDeclaration* ast);
	virtual void ProcessTypeName(const TypeName* ast);
	virtual void Visit(AST* ast);
public:
	ASTFileWriter(const char* filePath);
	ASTFileWriter(ASTFileWriter&& obj) = default;

	void WriteAST(AST* ast);
};
