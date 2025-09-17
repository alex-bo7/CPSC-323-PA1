#pragma once
#include <string>
#include <fstream>
#include <unordered_map>

class Scanner
{
public:
	Scanner(const std::string& fileName);

	void scanner();
	void printLexemeToken();

private:
	std::fstream inputFile;

	enum TOKEN {
		IDENTIFIER,
		INTEGER,
		KEYWORD,
		OPERATOR,
		PUNCTUATION,
		STRING
	};

	std::string tokenToString(const TOKEN& token);

	std::unordered_map<std::string, TOKEN> lexemeTokenPairs;

	bool isWhitespace(const char& ch);
	bool isAlphabet(const char& ch);
	bool isKeyword(const std::string& pattern);
	bool isDigit(const char& ch);
	bool isOperator(const std::string& pattern);
	bool isPuntuation(const char& ch);
	bool isComment(const char& ch);

	void commentToken(char& ch);
};