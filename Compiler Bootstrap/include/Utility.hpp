#pragma once
#include <string>

namespace Utility{
class String{
public:
	static bool IsPrefix(const std::string& str, const std::string& prefix);
	static bool IsSuffix(const std::string& str, const std::string& suffix);
	static bool HasCharacter(const std::string& str, char c);
};

class Character{
public:
	static bool IsDigit(char c);
};
}
