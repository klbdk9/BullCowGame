#pragma once

#include "FBullCowGame.h"

#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "cat";	// this MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))		// if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))		// if guess isn't lowercase
	{ 
		return EGuessStatus::Not_Lowercase;
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
	BullCowCount.CoveredWord = CoverWord();

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
					BullCowCount.CoveredWord = UncoverWord(BullCowCount.CoveredWord, MyHiddenWord[HiddenWordChar], GuessChar);
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

FString FBullCowGame::SetHiddenWord(int32)
{
	return FString();
}

FString FBullCowGame::CoverWord()
{
	FString CoverUpWord = "";

	do
	{
		CoverUpWord += "*";
	} while ((signed)CoverUpWord.length() < GetHiddenWordLength());

	return CoverUpWord;
}

FString FBullCowGame::UncoverWord(FString CoveredWord, char ShowChar, int32 CharPlace)
{
	FString UncoveredWord = CoveredWord;

	UncoveredWord[CharPlace] = ShowChar;

	return UncoveredWord;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

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

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}

