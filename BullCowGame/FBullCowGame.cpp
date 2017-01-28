#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { reset(); } // default constructor

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

int32 FBullCowGame::getMaxTries() const 
{ 
	TMap<int32, int32> wordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return wordLengthToMaxTries[myHiddenWord.length()]; 
}

void FBullCowGame::reset()
{
	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	myHiddenWord = HIDDEN_WORD;

	myCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
	if (!isIsogram(guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!isLowercase(guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != getHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
	// increment the turn number
	myCurrentTry++;

	// setup a return variable
	FBullCowCount bullCowCount;

	// loop through all letters in the hidden word
	int32 wordLength = myHiddenWord.length(); // assuming same length as guess
	for (int32 mHWChar = 0; mHWChar < wordLength; mHWChar++) 
	{	
		// compare letters against the guess
		for (int32 gChar = 0; gChar < wordLength; gChar++) 
		{
			// if they match then
			if (guess[gChar] == myHiddenWord[mHWChar]) 
			{
			// if they're in the same place
				if (mHWChar == gChar) 
				{
					bullCowCount.bulls++;		// increment bulls
				}
				else 
				{
					bullCowCount.cows++;		// increment cows
				}
			}
		}
	}

	if (bullCowCount.bulls == wordLength) 
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}

	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
	// treat 0 and 1 letter words as isograms
	if (word.length() <= 1) { return true; }

	// set up our map
	TMap <char, bool> letterSeen;
	for (auto letter : word) //for all letters of the word
	{
		letter = tolower(letter);		// handle mixed case
		if (letterSeen[letter]) {		// if the letter is in the map
			return false;				// we do NOT have an isogram
		}
		else {
			letterSeen[letter] = true;	// otherwise, add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString word) const
{
	for (auto letter : word) 
	{
		if (!islower(letter)) 
		{
			return false;
		}
	}

	return true;
}
