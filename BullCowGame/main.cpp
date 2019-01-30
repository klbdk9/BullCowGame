/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic see FBullCowGame class.
*/
#pragma once

#include "FBullCowGame.h"
#include "TextFileFunctions.h"

#include <iostream>
#include <string>

// make syntax Unreal friendly
using FText = std::string;
using int32 = int;

int main();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, re-used across plays

// entry point for application
/*
int32 main() 
{
	bool bPlayAgain = false;

	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;	// exit application
}
*/

int32 main()
{
	std::cout << TextFileFunctions::SelectRandomWordByLength(5);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "INFO: A bull is a correct letter in the correct place.\n";
	std::cout << "A cow is the correct letter but in the wrong place.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single round to win or lose
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// ask for guesses while game is NOT won and there are tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)			
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); // submit valid guess to game

		std::cout << "Bulls = " << BullCowCount.Bulls;			// print number of bulls and cows
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		std::cout << "Word: " << BullCowCount.CoveredWord << std::endl; // TODO Only show on Beginner difficulty

		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}

// loop until user provides valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only use lowercase letters.\n";
			break;

		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;

		default:		// assume guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK);		// loop until no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WON!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}