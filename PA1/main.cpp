#include <iostream>
#include <fstream>
#include <string>

int main() 
{
	std::string userFile = "text.txt";
	std::ifstream inputFile(userFile);

	if (!inputFile.is_open()) {
		std::cerr << "Problem opening file: " << userFile << std::endl;
		return 1;
	}

	char ch;
	std::string continousWord;

	while (inputFile.get(ch))
	{
		if (ch != ' ') // replace with ASCII?
		{
			std::cout << ch << std::endl;
			//continousWord += ch;
		}
		else
			std::cout << "SPACE" << std::endl;
	}

	inputFile.close();

	std::cout << continousWord << std::endl;

	continousWord = ""; // reset word every iteration

	return 0;
}