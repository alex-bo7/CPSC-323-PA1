#include <iostream>
#include <fstream>
#include <string>

#include "Scanner.h"

int main() 
{
	//Scanner myScanner("random.txt");
	Scanner myScanner("input_sourcecode.txt");

	myScanner.scanner();
	myScanner.printLexemeToken();

	//inputFile.close();

	return 0;
}