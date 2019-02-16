#pragma once
#include <vector>
#include <string>

/***** Abstract Syntax Tree *****/
class AST{
public:
	enum Type{
		EXPRESSION,
		INTEGER_LITERAL,
		BOOLEAN_LITERAL,
		IDENTIFIER
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
	virtual Type GetASTNodeType() const  = 0;
};
typedef AST::Type ASTNodeType;

/***** Expression *****/
class Expression : public AST{
public:
	enum Operation{
		POSITIVE,
		NEGATIVE,
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
		REMAINDER,
		LOGICAL_NOT,
		LOGICAL_AND,
		LOGICAL_OR,
		EQ,
		NEQ,
		LT,
		LTEQ,
		GT,
		GTEQ,
		BITWISE_NOT,
		BITWISE_AND,
		BITWISE_OR,
		BITWISE_XOR,
		SHIFT_LEFT,
		SHIFT_RIGHT
	};
public:
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

/***** Boolean Literal *****/
class BooleanLiteral : public AST{
public:
	bool value;
public:
	BooleanLiteral() = default;
	BooleanLiteral(const BooleanLiteral& obj) = default;
	BooleanLiteral(BooleanLiteral&& obj) = default;
	BooleanLiteral(const std::string& literal);

	BooleanLiteral& operator=(const BooleanLiteral& obj) = default;

	virtual ASTNodeType GetASTNodeType() const;
};

/***** Identifier *****/
class Identifier : public AST{
public:
	std::string symbol;
public:
	Identifier() = default;
	Identifier(const Identifier& obj) = default;
	Identifier(Identifier&& obj) = default;
	Identifier(const std::string& symbol);

	Identifier& operator=(const Identifier& obj) = default;

	virtual ASTNodeType GetASTNodeType() const;
};
