#include "Scanner.h"
#include <iostream>
#include <iomanip>
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

				inputFile.unget();

				if (isKeyword(pattern))
				{
					lexemeTokenPairs.insert({ pattern, KEYWORD });
				}
				else
				{
					lexemeTokenPairs.insert({ pattern, IDENTIFIER });
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

				inputFile.unget();

				if (pattern.size() > 1 && pattern[0] == '0')
					//displayLexemeToken(pattern, "INVALID");
					int a;
				else
					lexemeTokenPairs.insert({ pattern, INTEGER });
			}
			else if (isOperator(std::string(1, ch))) // OPERATOR
			{
				if (isComment(ch))
				{
					commentToken(ch);
				}
				else
				{
					std::string pattern;
					pattern += ch;

					inputFile.get(ch);

					if (!isWhitespace(ch))
						pattern += ch;

					if (isOperator(pattern))
						lexemeTokenPairs.insert({ pattern, OPERATOR });
					else
					{
						inputFile.unget();
						lexemeTokenPairs.insert({ std::string(1, ch), OPERATOR });
					}
				}

			}
			else if (isPuntuation(ch)) // PUNCTUATION
			{
				lexemeTokenPairs.insert({ std::string(1, ch), PUNCTUATION });
			}
			else if (ch == '\"') // STRING
			{
				std::string pattern;
				pattern += ch;
				while (inputFile.get(ch))
				{
					if (ch == '\"')
					{
						pattern += ch;
						break;
					}
					pattern += ch;
				}
				lexemeTokenPairs.insert({ pattern, STRING });
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

void Scanner::printLexemeToken()
{
	std::unordered_map<TOKEN, std::string> tokenCount;

	for (const auto& pair : lexemeTokenPairs)
	{
		tokenCount[pair.second] += pair.first; // insert key, increase value count
	}

	std::cout << std::left << std::setw(16) << "Token" << "Lexemes" << std::endl;
	std::cout << std::string(23, '-') << std::endl;

	for (const auto& pair : tokenCount)
	{
		std::cout << std::left << std::setw(10) 
			<< tokenToString(pair.first) << "\t" << pair.second << std::endl;
	}
}

std::string Scanner::tokenToString(const TOKEN& token)
{
	switch (token)
	{
	case IDENTIFIER : return "IDENTIFIER";
	case INTEGER: return "INTEGER";
	case KEYWORD: return "KEYWORD";
	case OPERATOR: return "OPERATOR";
	case PUNCTUATION: return "PUNCTUATION";
	case STRING: return "STRING";
	default: return "UNKNOWN";
	}
}

bool Scanner::isWhitespace(const char& ch)
{
	const std::unordered_set<char> WHITESPACE {
		' ', '\t', '\n'
	};

	return WHITESPACE.find(ch) != WHITESPACE.end();
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
		"int",
		"return"
	};

	return KEYWORD.find(pattern) != KEYWORD.end();
}

bool Scanner::isDigit(const char& ch)
{
	return (ch >= '0' && ch <= '9');
}

bool Scanner::isOperator(const std::string& pattern)
{
	const std::unordered_set<std::string> OPERATOR {
		"+", "-", "*", "/", "%",
		"++", "--",
		">", "<", ">=", "<=", "==",
		"="
	};

	return OPERATOR.find(pattern) != OPERATOR.end();
}

bool Scanner::isPuntuation(const char& ch)
{
	const std::unordered_set<char> PUNCTUATION{
		'(', ')', '{', '}', ';'
	};

	return PUNCTUATION.find(ch) != PUNCTUATION.end();
}


bool Scanner::isComment(const char& ch)
{
	return ( ch == '/' && (inputFile.peek() == '/' || inputFile.peek() == '*') );
}

void Scanner::commentToken(char& ch)
{
	if (inputFile.peek() == '/')
	{
		// consume until newline
		std::string pattern;
		pattern += ch;
		while (inputFile.get(ch))
		{
			if (ch == '\n')
				break;
			pattern += ch;
		}
		//displayLexemeToken(pattern, "COMMENT");

	}
	else
	{
		// consume until */
		std::string pattern;
		pattern += ch;
		while (inputFile.get(ch))
		{
			if (ch == '/')
				break;
			if (!isWhitespace(ch))
				pattern += ch;
		}
		pattern += ch;
		//displayLexemeToken(pattern, "COMMENT");
	}
}