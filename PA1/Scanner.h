#pragma once
#include <string>
#include <fstream>

class Scanner
{
public:
	Scanner(const std::string& fileName);

	void scanner();

private:
	std::fstream inputFile;

	bool isWhitespace(const char& ch);
	bool isPuntuation(const char& ch);
	bool isAlphabet(const char& ch);
	bool isKeyword(const std::string& pattern);
	bool isDigit(const char& ch);
	bool isOperator(const std::string& pattern);
};