#pragma once

#include "FBullCowGame.h"
#include "TextFileFunctions.h"

#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetEasyLength() const { return EasyLength; }
int32 FBullCowGame::GetHardLength() const { return HardLength; }
int32 FBullCowGame::GetDifficulty() const { return Difficulty; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 7}, {5, 10}, {6, 12}, {7, 15}, {8, 17}, {9, 20}, {10, 22}, {11, 24}, {12, 25}, {13, 26}, {14, 27}, {15, 5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	srand(time(NULL));

	const int32 WORD_LENGTH = rand() % (FBullCowGame::GetDifficulty() - 3) + 3;
	const FString HIDDEN_WORD = SetHiddenWord(WORD_LENGTH);	// this MUST be an isogram
//	const FString HIDDEN_WORD = "scope";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::SetDifficulty(FString Difficulty)
{
	int32 WordLength = 1;

	if (Difficulty == "easy")
	{
		WordLength = FBullCowGame::GetEasyLength();
	}
	else if (Difficulty == "hard")
	{
		WordLength = FBullCowGame::GetHardLength();
	}

	FBullCowGame::Difficulty = WordLength;

	return FBullCowGame::Difficulty; // TODO Check entire method & calls for redundant code
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
					BullCowCount.CoveredWord = UncoverLetter(BullCowCount.CoveredWord, MyHiddenWord[HiddenWordChar], GuessChar);
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

FString FBullCowGame::SetHiddenWord(int32 TheLength)
{
	FString RandomHiddenWord = TextFileFunctions::SelectRandomWordByLength(TheLength);

	return RandomHiddenWord;
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

FString FBullCowGame::UncoverLetter(FString CoveredWord, char ShowChar, int32 CharPlace)
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

