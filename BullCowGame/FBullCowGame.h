#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount		// two integers initialized to 0
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	bool CheckGuessValidity(FString) const; // TODO use a more rich return value

	void Reset();			// TODO use a more rich return value and input
	FBullCowCount SubmitGuess(FString);

private:					// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;

};