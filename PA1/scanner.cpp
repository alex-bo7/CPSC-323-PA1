#include "Scanner.h"
#include <iostream>
#include <unordered_set>

Scanner::Scanner(const std::string& fileName)
{
	inputFile.open(fileName);

	if (!inputFile.is_open())
	{
		std::cerr << "Problem opening file: " << fileName << std::endl;
		return;
	}
}

void Scanner::scanner()
{
	char ch;
	while (inputFile.get(ch))
	{
		if (!isWhitespace(ch))
		{
			//std::cout << ch << std::endl;
			if (isAlphabet(ch) || ch == '_') // KEYWORD or IDENTIFIER
			{
				std::string pattern;
				pattern += ch;
				while (inputFile.get(ch))
				{
					if (isWhitespace(ch) || isPuntuation(ch))
						break;

					pattern += ch;
					//if (pattern == "__") // invalid??
					//	break;
				}

				// NO continue here incase of chars being right next to words, it will skip them
				if (isKeyword(pattern))
				{
					std::cout << pattern << "\t KEYWORD" << std::endl;
				}
				else
				{
					std::cout << pattern << "\t IDENTIFIER" << std::endl;
				}
			}
			else if (isDigit(ch)) // INTEGER
			{
				std::string pattern;
				pattern += ch;
				while (inputFile.get(ch))
				{
					if (!isDigit(ch))
						break;
					pattern += ch;
				}

				if (pattern.size() > 1 && pattern[0] == '0')
				{
					std::cout << pattern << "\t INVALID" << std::endl;
					continue;
				}
				else
				{
					std::cout << pattern << "\t INTEGER" << std::endl;
					continue;
				}
			}
			else if (isOperator(ch)) // OPERATOR
			{
				std::cout << ch << "\t OPERATOR" << std::endl;
				continue;
			}
			else if (isPuntuation(ch)) // PUNCTUATION
			{
				std::cout << ch << "\t PUNCTUATION" << std::endl;
				continue;
			}
			else if (ch == '\"') // STRING
			{
				std::string pattern;
				pattern += ch;
				while (inputFile.get(ch))
				{
					if (ch == '\"')
						break;
					pattern += ch;
				}
				std::cout << pattern << "\t STRING" << std::endl;
				continue;
			}
			else if (ch == '/')
			{
				// comment
			}
			else
			{
				// ad hoc
				/*std::cout << ch << "\t INVALID" << std::endl;
				return;*/
			}
		}
		else
		{
			// final decision?
		}
	}
}

bool Scanner::isWhitespace(const char& ch)
{
	const std::unordered_set<char> WHITESPACE {
		' ', '\t', '\n'
	};

	return WHITESPACE.find(ch) != WHITESPACE.end();
}

bool Scanner::isPuntuation(const char& ch)
{
	const std::unordered_set<char> PUNCTUATION {
		'(', ')', '{', '}', ';'
	};

	return PUNCTUATION.find(ch) != PUNCTUATION.end();
}

bool Scanner::isAlphabet(const char& ch)
{
	return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

bool Scanner::isKeyword(const std::string& pattern)
{
	const std::unordered_set<std::string> KEYWORD {
		"if", "else",
		"for", "while",
		"int"
	};

	return KEYWORD.find(pattern) != KEYWORD.end();
}

bool Scanner::isDigit(const char& ch)
{
	return (ch >= '0' && ch <= '9');
}

bool Scanner::isOperator(const char& ch)
{
	const std::unordered_set<char> OPERATOR {
		'+', '-', '*', '/', '%'
	};

	return OPERATOR.find(ch) != OPERATOR.end();
}