// Fill out your copyright notice in the Description page of Project Settings.


#include "SBullCowPrototype.h"


// Sets default values
ASBullCowPrototype::ASBullCowPrototype()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ResetGame();

}

// Called when the game starts or when spawned
void ASBullCowPrototype::BeginPlay()
{
	Super::BeginPlay();
	sync();

}

// Called every frame
void ASBullCowPrototype::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBullCowPrototype::sync() {
    FString base = "This is world cup";
	constexpr int32 yearBook = 2022;
	base.Append(" ----------- ");
	base.Append(FString::FromInt(yearBook));
	UE_LOG(LogTemp, Log, TEXT("%s"), *base);
}

int32 ASBullCowPrototype::GetCurrentTry() const { return MyCurrentTry; }
int32 ASBullCowPrototype::GetHiddenWordLength() const { return MyHiddenWord.Len(); }
bool ASBullCowPrototype::IsGameWon() const { return bGameIsWon; }

int32 ASBullCowPrototype::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.Len()];
}

void ASBullCowPrototype::ResetGame()
{
	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus ASBullCowPrototype::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.Len() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, incriments turn, and returns count
FBullCowCount ASBullCowPrototype::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.Len(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool ASBullCowPrototype::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.Len() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;// add the letter to the map
		}
	}

	return true; // for example in cases where /0 is entered
}

bool ASBullCowPrototype::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}