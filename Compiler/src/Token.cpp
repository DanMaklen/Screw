#include "Token.hpp"
#include "Utility.hpp"
#include "Logger.hpp"
using namespace std;
using namespace Utility;

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
