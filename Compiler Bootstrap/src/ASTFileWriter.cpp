#include "ASTFileWriter.hpp"
using namespace std;

ASTFileWriter::ASTFileWriter(const char* filePath) : astFile(filePath){}

void ASTFileWriter::WriteAST(AST* ast){
	this->Visit(ast);
}

string ASTFileWriter::GetString_ASTNodeType(ASTNodeType astNodeType){
	switch(astNodeType){
		case ASTNodeType::EXPRESSION: return "EXPRESSION";
		case ASTNodeType::INTEGER_LITERAL: return "INTEGER_LITERAL";
		case ASTNodeType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
		case ASTNodeType::IDENTIFIER: return "IDENTIFIER";
		case ASTNodeType::AST_LIST: return "AST_LIST";
		case ASTNodeType::IF: return "IF";
		case ASTNodeType::WHILE: return "WHILE";
		default: return "?????UNKNOWN?????";
	}
}
string ASTFileWriter::GetString_ASTListType(ASTList::Type listType){
	switch(listType){
		case ASTList::Type::STATEMENT_LIST: return "STATEMENT_LIST";
		case ASTList::Type::EXPRESSION_LIST: return "EXPRESSION_LIST";
		default: return "?????UNKNOWN?????";
	}
}
string ASTFileWriter::GetString_TypeNameType(TypeName::Type typeNameType){
	switch(typeNameType){
		case TypeName::Type::INTEGER: return "INTEGER";
		case TypeName::Type::CHARACTER: return "CHARACTER";
		case TypeName::Type::BOOLEAN: return "BOOLEAN";
		case TypeName::Type::USER_DEFINED: return "USER_DEFINED";
		default: return "?????UNKNOWN?????";
	}
}
string ASTFileWriter::GetString_ExpressionOperation(Expression::Operation operation){
	switch(operation){
		case Expression::Operation::POSITIVE: return "+ (unary)";
		case Expression::Operation::NEGATIVE: return "- (unary)";
		case Expression::Operation::ADDITION: return "+";
		case Expression::Operation::SUBTRACTION: return "-";
		case Expression::Operation::MULTIPLICATION: return "*";
		case Expression::Operation::DIVISION: return "/";
		case Expression::Operation::REMAINDER: return "%";
		case Expression::Operation::LOGICAL_NOT: return "not";
		case Expression::Operation::LOGICAL_AND: return "and";
		case Expression::Operation::LOGICAL_OR: return "or";
		case Expression::Operation::EQ: return "==";
		case Expression::Operation::NEQ: return "!=";
		case Expression::Operation::LT: return "<";
		case Expression::Operation::LTEQ: return "<=";
		case Expression::Operation::GT: return ">";
		case Expression::Operation::GTEQ: return ">=";
		case Expression::Operation::BITWISE_NOT: return "~";
		case Expression::Operation::BITWISE_AND: return "&";
		case Expression::Operation::BITWISE_OR: return "|";
		case Expression::Operation::BITWISE_XOR: return "^";
		case Expression::Operation::SHIFT_LEFT: return "<<";
		case Expression::Operation::SHIFT_RIGHT: return ">>";
		case Expression::Operation::ASSIGNMENT: return "=";
		default: return "?????UNKNOWN?????";
	}
}
string ASTFileWriter::GetString_IntegerLiteralSize(IntegerLiteral::Size size){
	switch(size){
		case IntegerLiteral::Size::INT8: return "INT8";
		case IntegerLiteral::Size::INT16: return "INT16";
		case IntegerLiteral::Size::INT32: return "INT32";
		case IntegerLiteral::Size::INT64: return "INT34";
		default: return "?????UNKNOWN?????";
	}
}
string ASTFileWriter::GetString_Boolean(bool boolean){
	return boolean ? "true" : "false";
}

void ASTFileWriter::Visit(AST* ast){
	astFile << "{";
	astFile << "\"ASTNodeType\":\"" << GetString_ASTNodeType(ast->GetASTNodeType()) << "\",";
	astFile << "\"Attributes\":"; this->Dispatch(ast); astFile << ",";
	astFile << "\"Children\":[";
	int cnt = 0;
	for(AST* child : ast->GetChildren()){
		if(child == nullptr) continue;
		if(cnt++ != 0) astFile << ",";
		this->Visit(child);
	}
	astFile << "]";
	astFile << "}";
}

void ASTFileWriter::ProcessExpression(const Expression* ast){
	astFile << "{";
	astFile << "\"Operation\":\"" << GetString_ExpressionOperation(ast->op) << "\"";
	astFile << "}";
}
void ASTFileWriter::ProcessIntegerLiteral(const IntegerLiteral* ast){
	astFile << "{";
	astFile << "\"value\":" << ast->value.int64 << ",";
	astFile << "\"size\":\"" << GetString_IntegerLiteralSize(ast->intSize) << "\",";
	astFile << "\"signedInt\":" << GetString_Boolean(ast->signedInt);
	astFile << "}";
}
void ASTFileWriter::ProcessBooleanLiteral(const BooleanLiteral* ast){
	astFile << "{";
	astFile << "\"value\":" << GetString_Boolean(ast->value);
	astFile << "}";
}
void ASTFileWriter::ProcessIdentifier(const Identifier* ast){
	astFile << "{";
	astFile << "\"symbol\":\"" << ast->symbol << "\"";
	astFile << "}";
}
void ASTFileWriter::ProcessASTList(const ASTList* ast){
	astFile << "{";
	astFile << "\"listType\":\"" << GetString_ASTListType(ast->listType) << "\"";
	astFile << "}";
}
void ASTFileWriter::ProcessIf(const If* ast){
	astFile << "{}";
}
void ASTFileWriter::ProcessWhile(const While* ast){
	astFile << "{}";
}
void ASTFileWriter::ProcessVariableDeclaration(const VariableDeclaration* ast){
	astFile << "{}";
}
void ASTFileWriter::ProcessTypeName(const TypeName* ast){
	astFile << "{";
	astFile << "\"listType\":\"" << GetString_TypeNameType(ast->type) << "\"";
	astFile << "}";
}
