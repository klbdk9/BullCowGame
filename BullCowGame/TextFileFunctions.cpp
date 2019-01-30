#include "TextFileFunctions.h"
#include <map>

#define TMap std::map

bool TextFileFunctions::PrintTextFileByLine(FString FileName)
{
	FString Line;
	std::ifstream AllWords(FileName);

	if (AllWords.is_open())
	{
		int LineCount = 0;
		while (std::getline(AllWords, Line))
		{
			std::cout << LineCount++ << ": ";
			std::cout << Line << '\n';
		}
		AllWords.close();
	}

	else
	{
		std::cout << "Unable to open file";
		return false;
	}

	return true;
}

bool TextFileFunctions::CreateIsogramList(FString Input, FString Output)
{
	FString Line;
	std::ifstream AllWords(Input);
	std::ofstream Isograms(Output);

	if (AllWords.is_open() && Isograms.is_open())
	{
		while (std::getline(AllWords, Line))
		{
			if (IsIsogram(Line))
			{
				Isograms << Line << std::endl;
			}
		}
		Isograms.close();
		AllWords.close();
	}

	else
	{
		std::cout << "Unable to open file";
		return false;
	}

	return true;
}

bool TextFileFunctions::SortListByWordLength(FString Input, FString Output)
{
	constexpr int32 MIN_WORD_LENGTH = 3;
	constexpr int32 MAX_WORD_LENGTH = 20;

	for (int CurrentLength = MIN_WORD_LENGTH; CurrentLength < MAX_WORD_LENGTH; CurrentLength++)
	{
		FString Line;
		std::ifstream AllWords(Input);
		std::ofstream SortedByLength(Output, std::ios_base::app);

		if (AllWords.is_open() && SortedByLength.is_open())
		{
			while (std::getline(AllWords, Line))
			{
				if (IsLength(Line, CurrentLength))
				{
					SortedByLength << Line << std::endl;
				}
			}
			SortedByLength.close();
			AllWords.close();
		}
		else
		{
			std::cout << "Unable to open file";
			return false;
		}
	}
	return true;
}

bool TextFileFunctions::AddIntMapping(FString Input, FString Output)
{
	return false;
}

FString TextFileFunctions::SelectRandomWordByLength(int32 TheLength)
{
	return FString();
}

bool TextFileFunctions::IsIsogram(FString Word)
{
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)			// loop all letters in the word
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool TextFileFunctions::IsLength(FString Word, int32 SetLength)
{
	if(Word.length() == SetLength)
		return true;

	return false;
}

