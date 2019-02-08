// TODO FULLY COMMENT CODE & make sure all methods/calls are clear
// TODO Spend a turn for a bull
// TODO Add dictionary with definitions

// TODO balancing word length to # of turns (only can be done by multiple play throughs, work in progress)
// TODO balancing difficulty (is 3-6 okay for easy and 6-11 okay for hard?)

// TODO GUI ASCII Art
// TODO GUI WARNING: Highly time consuming. Add Pleasant GUI, graphics. possibly refactor to mobile game

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
	Not_Difficulty,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetMinLength() const;
	int32 GetMaxLength() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	EDifficultyStatus CheckDifficultyValidity(FString) const;

	void Reset();
	void SetValidDifficulty(FString);
	FBullCowCount SubmitValidGuess(FString);

private:					// see constructor for initialization
	int32 MyCurrentTry;
	int32 MinLength;
	int32 MaxLength;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsValidDifficulty(FString) const;

	FString SetHiddenWord(int32);
	FString CoverWord();
	FString UncoverLetter(FString, char, int32);

};