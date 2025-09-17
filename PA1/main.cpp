#include <iostream>
#include <fstream>
#include <string>

#include "Scanner.h"

int main() 
{
	char again = 'y';
	while (again == 'y')
	{
		std::cout << "Enter text file name only: ";
		std::string fileName;
		std::cin >> fileName;

		fileName += ".txt";
		std::cout << std::endl;

		Scanner myScanner(fileName);

		myScanner.scanner();
		myScanner.printLexemeToken();

		std::cout << "\nScan another file? y|n  ";
		std::cin >> again;
		std::cout << std::endl;
	}

	return 0;
}