#include "TextFileFunctions.h"
#include <time.h>
#include <algorithm>
#include <map>

#define TMap std::map

const char * TextFileFunctions::WORD_BANK = "../SortedIsoLower.txt";
// TODO see Dictionary_Notes.txt
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

int32 TextFileFunctions::NumberOfLines(FString FileName)
{
	int32 LineCount = 0;
	FString Line;
	std::ifstream TheFile(FileName);
	
	while ( std::getline(TheFile, Line) )
	{
		++LineCount;
	}

	return LineCount;
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

bool TextFileFunctions::SortIsogramByWordLength(FString Input, FString Output)
{
	constexpr int32 MIN_WORD_LENGTH = 3;
	constexpr int32 MAX_WORD_LENGTH = 26;

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

FString TextFileFunctions::SelectRandomWordByLength(int32 TheLength)
{
	FString Line;
	std::ifstream File(WORD_BANK);

	FWordIndex WordIndexes = TextFileFunctions::SelectWords(TheLength);

	srand (time(NULL));

	int32 RandomInt = rand() % (WordIndexes.end - WordIndexes.start + 1);
	RandomInt = RandomInt + WordIndexes.start + 1;
	int32 LineNumber = 1;

	while (getline(File, Line))
	{
		++LineNumber; 
		if (LineNumber == RandomInt)
		{
			File.close();
			return Line;
		}
	}

	return Line;
}

bool TextFileFunctions::FileToLowercase(FString Input, FString Output)
{
	FString Line;
	std::ifstream File(Input);
	std::ofstream Lowercase(Output);

	if (File.is_open() && Lowercase.is_open())
	{
		while (std::getline(File, Line))
		{
			std::transform(Line.begin(), Line.end(), Line.begin(), ::tolower);
			Lowercase << Line << std::endl;
		}

		File.close();
		Lowercase.close();
	}
	else
	{
		std::cout << "Unable to open file";
		return false;
	}

	return true;
}

bool TextFileFunctions::FormatDefinitions(FString Input, FString Output)  // TODO reformat definitions to display word type at beginning of def, and remove suffixes (instead of [n -ED -S], just display [noun]) 
{
	FString Line; // TODO make sure naming is clear and consistent
	std::ifstream File(Input);
	std::ofstream DefFormat(Output);

	if (File.is_open() && DefFormat.is_open())
	{
		while (std::getline(File, Line))
		{
			size_t space = Line.find('\t');
			FString word = Line.substr(0, space);
			FString def = Line.substr(space);

			while (def.substr(0, 1) == "\t")
			{
				def = def.substr(1);
			}

			Line = word + ": " + def;

			DefFormat << Line << std::endl;
		}

		File.close();
		DefFormat.close();
	}
	else
	{
		std::cout << "Unable to open file";
		return false;
	}

	return true;
}

FWordIndex TextFileFunctions::SelectWords(int32 TheLength)
{
	FWordIndex WordRange;

	FString Line;
	std::ifstream File(WORD_BANK);

	int32 Count = 0;
	bool CountingWords = false;
	int32 WordsOfLength = 0;

	while (getline(File, Line))
	{
		Count++;
		if ( IsLength(Line, TheLength) && !CountingWords )
		{
			WordRange.start = Count;
			CountingWords = 1;
			WordsOfLength++;
		}
		else if ( IsLength(Line, TheLength) && CountingWords )
		{
			WordsOfLength++;
		}
		else if ( !IsLength(Line, TheLength) && CountingWords )
		{
			break;
		}
	}
	File.close();

	WordRange.end = WordRange.start + WordsOfLength - 1;

	return WordRange;
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

