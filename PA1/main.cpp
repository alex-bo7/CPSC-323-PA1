#include <iostream>
#include <fstream>
#include <string>

#include "Scanner.h"

const std::string OUTPUT_FILE_NAME = "Output";
const std::string TEXT_EXTENSION = ".txt";

int main() 
{
	int filesCreatedCount = 0;
	char again = 'y';
	while (again == 'y')
	{
		std::cout << "Enter text file name only: ";
		std::string fileName;
		std::cin >> fileName;

		fileName += TEXT_EXTENSION;
		std::cout << std::endl;

		Scanner myScanner(fileName);

		myScanner.scanner();
		myScanner.printLexemeToken(std::cout);

		std::string outputFileName;
		if (filesCreatedCount == 0)
			outputFileName = OUTPUT_FILE_NAME + TEXT_EXTENSION;
		else
			outputFileName = OUTPUT_FILE_NAME + std::to_string(filesCreatedCount) + TEXT_EXTENSION;
		myScanner.saveToFile(outputFileName);

		std::cout << "\nScan another file? y|n  ";
		std::cin >> again;
		std::cout << std::endl;

		++filesCreatedCount;
	}

	return 0;
}