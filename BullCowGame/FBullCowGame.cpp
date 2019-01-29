#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)		// if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;			// TODO write function
	}
	else if (false)		// if guess isn't lowercase
	{ 
		return EGuessStatus::Not_Lowercase;			// TODO write function
	}
	else if ( Guess.length() != GetHiddenWordLength() )		// if guess length is wrong
	{ 
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();											// assume hidden word is same length as guess
	for (int32 HiddenWordChar = 0; HiddenWordChar < WordLength; HiddenWordChar++)		// loop through all letters in the hidden word
	{	
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)					// compare letters against the guess
		{
			if (Guess[GuessChar] == MyHiddenWord[HiddenWordChar])
			{
				if (HiddenWordChar == GuessChar)
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}
