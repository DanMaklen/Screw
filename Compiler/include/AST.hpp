#pragma once
#include <vector>
#include <string>

/***** Abstract Syntax Tree *****/
class AST{
public:
	enum ASTNodeType{
		EXPRESSION,
		INTEGER_LITERAL
	};
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
typedef AST::ASTNodeType ASTNodeType;

/***** Expression *****/
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
public:
	Expression(Operation op, AST* operand);
	Expression(Operation op, AST* operand1, AST* operand2);
	Expression(Operation op, AST* operand1, AST* operand2, AST* operand3);

	virtual ASTNodeType GetASTNodeType() const;
	Operation GetOperation() const;
};

/***** Integer Literal *****/
class IntegerLiteral : public AST{
public:
	enum Size{
		INT8,
		INT16,
		INT32,
		INT64
	};
private:
	bool HasBasePrefix(const std::string& literal);
	int GetBase(const std::string& literal);
	Size GetIntegerSize(const std::string& literal);
	int GetDigitValue(char);
	long long GetValue(const std::string& literal, int base);
public:
	union{
		unsigned char int8;
		unsigned short int16;
		unsigned int int32;
		unsigned long long int64;
	} value;
	Size intSize;
	bool signedInt;

	IntegerLiteral() = default;
	IntegerLiteral(const IntegerLiteral& obj) = default;
	IntegerLiteral(IntegerLiteral&& obj) = default;
	IntegerLiteral(const std::string& literal);

	IntegerLiteral& operator=(const IntegerLiteral& obj) = default;

	virtual ASTNodeType GetASTNodeType() const;
};
