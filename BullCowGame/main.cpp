/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void playGame();
void printIntro();
FText getValidGuess();
bool askToPlayAgain();
void printGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse acrpss plays

// the entry point for our application
int main() 
{
	bool bPlayAgain = false;
	do {
		printIntro();
		playGame();
		bPlayAgain =  askToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0; // exit the application
}

void printIntro() 
{

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Try to guess the " << BCGame.getHiddenWordLength();
	std::cout << " letter isogram that I'm thinking of." << std::endl;
	std::cout << std::endl;

	return;
}

// plays a single game to completion
void playGame()
{
	BCGame.reset();

	int32 maxTries = BCGame.getMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries) 
	{
		FText Guess = getValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount bullCowCount = BCGame.submitValidGuess(Guess);

		std::cout << "Bull = " << bullCowCount.bulls << std::endl;
		std::cout << "Cows = " << bullCowCount.cows << "\n\n";
	}

	printGameSummary();
	return;
}

// loop continually until user submits a valid guess
FText getValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do {
		// get a guess from the player
		int32 currentTry = BCGame.getCurrentTry();

		std::cout << "Guess # " << currentTry << " of " << BCGame.getMaxTries() << " . Guess a word : ";
		std::getline(std::cin, guess);

		// check status and give feedback
		status = BCGame.checkGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n" << std::endl;
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (status != EGuessStatus:: OK); // keep looping until we get no errors

	return guess;
}

bool askToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (Y|N)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void printGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "WELL DONE - YOU WIN\n" << std::endl;
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME - YOU LOSE\n" << std::endl;
	}
}
