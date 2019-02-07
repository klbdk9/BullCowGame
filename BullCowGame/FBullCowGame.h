// TODO ASCII Art?
// TODO choose word length from 3 - 15(?)
// TODO dictionary of isograms chosen at random
// TODO Hint system. Spend a turn for a hint
// TODO choose Difficulty (Beginner, Easy, Medium, Hard)
// TODO Show bulls as letters and rest of word as *'s on Beginner and EASY with more than 7 letters

#pragma once

#include <string>

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

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:					// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	FString SetHiddenWord(int32);
	FString CoverWord();
	FString UncoverLetter(FString, char, int32);

};