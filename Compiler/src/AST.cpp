#include "AST.hpp"
using namespace std;

AST::AST(const vector<AST*>& children) : children(children){}
const vector<AST*>& AST::GetChildren() const{
	return children;
}

Expression::Expression(Operation op, AST* operand) : op(op), AST({operand, nullptr, nullptr}){}
Expression::Expression(Operation op, AST* operand1, AST* operand2) : op(op), AST({operand1, operand2, nullptr}){}
Expression::Expression(Operation op, AST* operand1, AST* operand2, AST* operand3) : op(op), AST({operand1, operand2, operand3}){}
ASTNodeType Expression::GetASTNodeType() const{
	return EXPRESSION;
}

TerminalValue::TerminalValue(const IntegerLiteral& intLiteral) : type(INTEGER_LITERAL) {
	value.intLiteral = intLiteral;
}
ASTNodeType TerminalValue::GetASTNodeType() const {
	return TERMINAL_VALUE;
}
