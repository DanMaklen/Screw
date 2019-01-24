#pragma once
#include "Token.hpp"
#include <vector>

enum ASTNodeType{
	EXPRESSION,
	TERMINAL_VALUE
};
class AST{
protected:
	std::vector<AST*> children;

	AST() = default;
	AST(const std::vector<AST*>& children);
	AST(const AST& obj) = default;
	AST(AST&& obj) = default;

	AST& operator=(const AST& obj) = default;
public:
	const std::vector<AST*>& GetChildren() const;
	virtual ASTNodeType GetASTNodeType() const  = 0;
};

class Expression : public AST{
public:
	enum Operation{
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
		REMAINDER
	};
private:
	Operation op;
	AST* operand[3];
public:
	Expression(Operation op, AST* operand);
	Expression(Operation op, AST* operand1, AST* operand2);
	Expression(Operation op, AST* operand1, AST* operand2, AST* operand3);

	virtual ASTNodeType GetASTNodeType() const;
};

class TerminalValue : public AST{
public:
	enum OperandType{
		INTEGER_LITERAL
	};
private:
	OperandType type;
	union{
		IntegerLiteral intLiteral;
	} value;
public:
	TerminalValue(const IntegerLiteral& intLiteral);

	virtual ASTNodeType GetASTNodeType() const;
};
