#pragma once

#include <fstream>
#include <iostream>
#include <string>

// make syntax Unreal friendly
using FString = std::string;
using int32 = int;

class TextFileFunctions
{
public:
	static bool PrintTextFileByLine(FString);
	static bool CreateIsogramList(FString, FString);
	static bool SortListByWordLength(FString, FString);
	static bool AddIntMapping(FString, FString);
	FString SelectRandomWordByLength(int32);

private:
	static bool IsIsogram(FString);
	static bool IsLength(FString, int32);
};