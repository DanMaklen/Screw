#include "AST.hpp"
#include "Utility.hpp"
using namespace std;
using namespace Utility;

/***** Abstract Syntax Tree *****/
AST::AST(const vector<AST*>& children) : children(children){}
const vector<AST*>& AST::GetChildren() const{
	return children;
}

/***** ListType *****/
ASTList::ASTList(ASTList::Type listType) : listType(listType){}
ASTNodeType ASTList::GetASTNodeType() const{
	return ASTNodeType::AST_LIST;
}
void ASTList::Append(AST* ast){
	this->children.push_back(ast);
}

/***** If Statement *****/
If::If(AST* condition, AST* trueClause) : AST({condition, trueClause}){}
If::If(AST* condition, AST* trueClause, AST* falseClause) : AST({condition, trueClause, falseClause}){}
ASTNodeType If::GetASTNodeType() const{
	return ASTNodeType::IF;
}

/***** While Statement *****/
While::While(AST* condition, AST* body) : AST({condition, body}){}
ASTNodeType While::GetASTNodeType() const{
	return ASTNodeType::WHILE;
}

/***** Expression *****/
Expression::Expression(Operation op, AST* operand) : op(op), AST({operand}){}
Expression::Expression(Operation op, AST* operand1, AST* operand2) : op(op), AST({operand1, operand2}){}
Expression::Expression(Operation op, AST* operand1, AST* operand2, AST* operand3) : op(op), AST({operand1, operand2, operand3}){}
ASTNodeType Expression::GetASTNodeType() const{
	return ASTNodeType::EXPRESSION;
}
Expression::Operation Expression::GetOperation() const{
	return op;
}

/***** Integer Literal *****/
bool IntegerLiteral::HasBasePrefix(const string& literal){
	return literal.size() >= 2 && literal[0] == '0' && String::HasCharacter("bBtToOcCdDhHxX", literal[1]);
}
int IntegerLiteral::GetBase(const string& literal){
	if(!HasBasePrefix(literal)) return 10;
	switch(literal[1]){
		case 'b': case 'B': return 2;
		case 't': case 'T': return 3;
		case 'o': case 'O': case 'c': case 'C': return 8;
		case 'd': case 'D': return 10;
		case 'h': case 'H': case 'x': case 'X': return 16;
		default: return 10;
	}
	return 10;
}
IntegerLiteral::Size IntegerLiteral::GetIntegerSize(const string& literal){
	if(String::IsSuffix(literal, "int8")) return Size::INT8;
	if(String::IsSuffix(literal, "int16")) return Size::INT16;
	if(String::IsSuffix(literal, "int32")) return Size::INT32;
	if(String::IsSuffix(literal, "int64")) return Size::INT64;
	return Size::INT32;
}
int IntegerLiteral::GetDigitValue(char digit){
	if('0' <= digit && digit <= '9') return digit - '0';
	if('a' <= digit && digit <= 'z') return digit - 'a' + 10;
	if('A' <= digit && digit <= 'Z') return digit - 'A' + 10;
	return 0;
}
long long IntegerLiteral::GetValue(const string& literal, int base){
	long long val = 0;
	for(int i = HasBasePrefix(literal) ? 2 : 0; i < literal.size(); i++){
		if(literal[i] == '`') continue;
		if(String::HasCharacter("suint", literal[i])) break;
		val = val * base + GetDigitValue(literal[i]);
	}
	return val;
}
IntegerLiteral::IntegerLiteral(const string& literal){
	this->signedInt = !String::HasCharacter(literal, 'u');
	this->intSize = GetIntegerSize(literal);
	this->value.int64 = GetValue(literal, GetBase(literal));
}
ASTNodeType IntegerLiteral::GetASTNodeType() const{
	return ASTNodeType::INTEGER_LITERAL;
}

/***** Boolean Literal *****/
BooleanLiteral::BooleanLiteral(const string& literal) : value(literal=="true"){}
ASTNodeType BooleanLiteral::GetASTNodeType() const{
	return ASTNodeType::BOOLEAN_LITERAL;
}

/***** Identifier *****/
Identifier::Identifier(const string& symbol) : symbol(symbol){}
ASTNodeType Identifier::GetASTNodeType() const{
	return ASTNodeType::IDENTIFIER;
}

/***** Variable Declaration *****/
VariableDeclaration::VariableDeclaration(AST* typeName, AST* variable) : AST({typeName, variable}){}
ASTNodeType VariableDeclaration::GetASTNodeType() const{
	return ASTNodeType::VARIABLE_DECLARATION;
}

/***** Type Name *****/
TypeName::TypeName(Type type) : type(type) {};
TypeName::TypeName(AST* userDefinedType) : type(TypeName::Type::USER_DEFINED), AST({userDefinedType}){}
ASTNodeType TypeName::GetASTNodeType() const{
	return ASTNodeType::TYPE_NAME;
}
