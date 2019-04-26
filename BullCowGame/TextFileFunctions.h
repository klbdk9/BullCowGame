#pragma once

#include <fstream>
#include <iostream>
#include <string>

// make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FWordIndex
{
	int32 start = 0;
	int32 end = 0;
};

class TextFileFunctions
{
public:
	static bool PrintTextFileByLine(FString);
	static int32 NumberOfLines(FString);
	static bool CreateIsogramList(FString, FString);
	static bool SortIsogramByWordLength(FString, FString);
	static FString SelectRandomWordByLength(int32);
	static bool FileToLowercase(FString, FString);
	static bool FormatDefinitions(FString Input, FString Output);

	static FWordIndex SelectWords(int32);

private:
	static bool IsIsogram(FString);
	static bool IsLength(FString, int32);

	const static char * WORD_BANK;
};