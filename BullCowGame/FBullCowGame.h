/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 bulls = 0;
	int32 cows = 0;

};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;

	void reset();
	FBullCowCount submitValidGuess(FString);

private:
	// see constructor for initialization
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;
	bool bGameIsWon;

	bool isIsogram(FString) const;
	bool isLowercase(FString) const;
};
