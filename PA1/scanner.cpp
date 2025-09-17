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
					displayLexemeToken(pattern, "KEYWORD");
				}
				else
				{
					displayLexemeToken(pattern, "IDENTIFIER");
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
					displayLexemeToken(pattern, "INVALID");
				else
					displayLexemeToken(pattern, "INTEGER");
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
						displayLexemeToken(pattern, "OPERATOR");
					else
					{
						inputFile.unget();
						displayLexemeToken(ch, "OPERATOR");
					}
				}

			}
			else if (isPuntuation(ch)) // PUNCTUATION
			{
				displayLexemeToken(ch, "PUNCTUATION");
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
				displayLexemeToken(pattern, "STRING");
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

template <typename T>
void Scanner::displayLexemeToken(const T& lexeme, const std::string& token)
{
	std::cout << std::left << std::setw(10) << lexeme
			  << std::setw(15) << token << std::endl;
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