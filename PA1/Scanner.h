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
	void matchToken(const std::string& pattern);
};