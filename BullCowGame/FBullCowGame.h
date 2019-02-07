// TODO ASCII Art?
// TODO balancing word length to # of turns
// TODO Spend a turn for a bull
// TODO choose Difficulty: (Easy, Hard) Easy has max word length of 6, Hard has word length 6+

#pragma once

#include <string>
#include <time.h>

// make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount		// two integers initialized to 0 and blank string
{
	int32 Bulls = 0;
	int32 Cows = 0;
	FString CoveredWord = "";
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK, 
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EDifficultyStatus
{
	Invalid_Status,
	OK,
	Not_Status,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetEasyLength() const;
	int32 GetHardLength() const;
	int32 GetDifficulty() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	int32 SetDifficulty(FString);
	FBullCowCount SubmitValidGuess(FString);

private:					// see constructor for initialization
	int32 MyCurrentTry;
	int32 EasyLength = 6;
	int32 HardLength = 15;
	int32 Difficulty = EasyLength;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	FString SetHiddenWord(int32);
	FString CoverWord();
	FString UncoverLetter(FString, char, int32);

};