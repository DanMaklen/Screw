#pragma once
#include <string>
#include "AST.hpp"

class Parser{
	Parser(const Parser&) = delete;
private:
public:
	Parser() = default;
	Parser(Parser&&) = default;

	AST* Parse(const std::string& filePath);
};
