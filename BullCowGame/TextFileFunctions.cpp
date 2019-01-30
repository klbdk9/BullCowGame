#pragma once

#include <iostream>
#include <fstream>
#include <string>

void TextFileFunctions()
{
	std::string Line;
	std::ifstream AllWords("ListOfWords.txt");

	if (AllWords.is_open())
	{
		while (getline(AllWords, Line))
		{
			std::cout << Line << '\n';
		}
		AllWords.close();
	}

	else
	{
		std::cout << "Unable to open file";
	}
}