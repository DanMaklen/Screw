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
		IDENTIFIER,
		AST_LIST,
		IF,
		WHILE,
		VARIABLE_DECLARATION,
		TYPE_NAME
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

/***** ASTList *****/
class ASTList : public AST{
public:
	enum Type{
		STATEMENT_LIST,
		EXPRESSION_LIST
	};
public:
	Type listType;
public:
	ASTList(Type listType);

	virtual ASTNodeType GetASTNodeType() const;

	void Append(AST* ast);
};

/***** If Statement *****/
class If : public AST{
public:
	If(AST* condition, AST* trueClause);
	If(AST* condition, AST* trueClause, AST* FalseClause);

	virtual ASTNodeType GetASTNodeType() const;
};

/***** While Statement *****/
class While : public AST{
public:
	While(AST* condition, AST* body);

	virtual ASTNodeType GetASTNodeType() const;
};

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
		SHIFT_RIGHT,
		ASSIGNMENT
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

	IntegerLiteral(const std::string& literal);

	virtual ASTNodeType GetASTNodeType() const;
};

/***** Boolean Literal *****/
class BooleanLiteral : public AST{
public:
	bool value;
public:
	BooleanLiteral(const std::string& literal);

	virtual ASTNodeType GetASTNodeType() const;
};

/***** Identifier *****/
class Identifier : public AST{
public:
	std::string symbol;
public:
	Identifier(const std::string& symbol);

	virtual ASTNodeType GetASTNodeType() const;
};

/***** Variable Declaration *****/
class VariableDeclaration : public AST{
public:
	VariableDeclaration(AST* typeName, AST* variable);

	virtual ASTNodeType GetASTNodeType() const;
};

/***** Type Name *****/
class TypeName : public AST{
public:
	enum Type{
		INTEGER,
		CHARACTER,
		BOOLEAN,
		USER_DEFINED
	};
public:
	Type type;
public:
	TypeName(Type type);
	TypeName(AST* userDefinedType);

	virtual ASTNodeType GetASTNodeType() const;
};
