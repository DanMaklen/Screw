#pragma once
#include <string>
#include <iostream>

class Logger{
public:
	enum Type{
		ERROR,
		WARNING,
		INFO
	};
private:
	template<typename T>
	static void Log(T&& arg){
		std::cout << arg << std::endl;
	}
	template<typename T, typename... Args>
	static void Log(T&& arg, Args&&... args){
		std::cout << arg << ' ';
		Log(args...);
	}

	static std::string MessageHeader(Type type);
public:

	template<typename... Args>
	static void Log(Type type, Args&&... args){
		std::cout << MessageHeader(type) << ' ';
		Log(args...);
	}
};
