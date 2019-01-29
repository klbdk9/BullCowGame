/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic see FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

int main();

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point for application
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

// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	for (int32 count = 1; count <= MaxTries; count++)			// loop for number of turns asking for guesses
	{															// TODO change from FOR to WHILE once we are validating tries
		FText Guess = GetGuess();								// TODO check for valid guesses

		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess); // submit valid guess to game

		std::cout << "Bulls = " << BullCowCount.Bulls;			// print number of bulls and cows
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}

	// TODO add a game summary
}

FText GetGuess()			// get a guess from the player
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
