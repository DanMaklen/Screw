#pragma once
#include <string>

class Parser{
	Parser(const Parser&) = delete;
private:
public:
	Parser() = default;
	Parser(Parser&&) = default;

	void Parse(const std::string& filePath);
};
