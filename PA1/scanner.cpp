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
		if (isWhitespace(ch))
			continue;
		else
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
					lexemeTokenPairs.insert({ pattern, ADHOC });
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

					char nextCh = inputFile.peek();
					std::string twoCharOperator = pattern + nextCh;

					if (isOperator(twoCharOperator))
					{
						inputFile.get(nextCh);
						lexemeTokenPairs.insert({ twoCharOperator, OPERATOR });
					}
					else
					{
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
				lexemeTokenPairs.insert({ std::string(1, ch), ADHOC });
			}
		}
	}

	groupLexemesTogether();
	inputFile.close();
}

void Scanner::groupLexemesTogether()
{
	for (const auto& pair : lexemeTokenPairs)
	{
		groupLexemes[pair.second] += pair.first; // add lexeme together with same TOKEN
	}
}

void Scanner::printLexemeToken(std::ostream& out)
{
	out << std::left << std::setw(16) << "Token" << "Lexemes" << std::endl;
	out << std::string(23, '-') << std::endl;

	for (const auto& pair : groupLexemes)
	{
		out << std::left << std::setw(10) 
			<< tokenToString(pair.first) << "\t" << pair.second << std::endl;
	}
}

void Scanner::saveToFile(const std::string & fileName)
{
	std::ofstream myFile(fileName); // creates or overrides

	if (myFile.is_open())
	{
		printLexemeToken(myFile);
		std::cout << "Saved to file: " << fileName << std::endl;
	} 
	else
	{
		std::cerr << "Problem opening file: " << fileName  << std::endl;
	}

	myFile.close();
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
		// Control flow
		"if", "else", "switch", "case", "default",
		"for", "while", "do", "break", "continue",

		// Data types
		"int", "float", "double", "char", "string", "bool", "void"

		// I/O
		"cin", "cout", "endl",

		// Functions
		"return", "auto",

		// Modifiers
		"const", "static",

		// Classes and objects
		"class", "struct", "public", "private", "protected", "new", "delete",

		// Logical values
		"true", "false"
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
		"+=", "-=", "*=", "/=","%=",
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