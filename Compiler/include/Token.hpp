#pragma once
#include <string>

class IntegerLiteral{
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
	long long GetValue(const std::string& digits, int base);
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
};
