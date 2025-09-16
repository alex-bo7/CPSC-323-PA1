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
	std::string pattern;
	while (inputFile.get(ch))
	{
		if (isWhitespace(ch))
		{
			// when meet ws that means end of continous pattern aka word
			// that is when we give it final identifier

			// give identifier at each ch and/or final at full word??

			std::cout << pattern << std::endl;
			pattern = "";
		}
		else
		{
			pattern += ch;
		}

		// SKIP COMMENTS
	}
	std::cout << pattern << std::endl;
}

bool Scanner::isWhitespace(const char& ch)
{
	const std::unordered_set<char> WHITESPACE {
		' ', '\t', '\n'
	};

	return WHITESPACE.find(ch) != WHITESPACE.end();
}

void Scanner::matchToken(const std::string& pattern)
{
	const std::unordered_set<char> IDENTIFIER {
		// a full word, check last range: a-zA-Z
	};

	const std::unordered_set<char> INTEGER {
		// any number except octal (start with 0) range 0-9+
	};

	const std::unordered_set<char> KEYWORD {
		' ', '\t', '\n' // if else while for
	};

	const std::unordered_set<char> OPERATOR {
		' ', '\t', '\n' // + = - /
	};

	const std::unordered_set<char> PUNCTUATION {
		' ', '\t', '\n' // ( {
	};

	const std::unordered_set<char> STRING {
		' ', '\t', '\n' // surrounded ""
	};
}