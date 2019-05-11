#include "Utility.hpp"
using namespace std;

namespace Utility{
bool String::IsPrefix(const string& str, const string& prefix){
	if(prefix.size() > str.size()) return false;
	for(int i = 0; i < prefix.size(); i++)
		if(str[i] != prefix[i])
			return false;
	return true;
}
bool String::IsSuffix(const string& str, const string& suffix){
	if(suffix.size() > str.size()) return false;
	for(int i = str.size()-1, j = suffix.size()-1; i >= 0 && j >= 0; i--, j--)
		if(str[i] != suffix[j])
			return false;
	return true;
}
bool String::HasCharacter(const string& str, char c){
	for(int i = 0; i < str.size(); i++)
		if(str[i] == c)
			return true;
	return false;
}

bool Character::IsDigit(char c){
	return '0' <= c && c <= '9';
}
}
