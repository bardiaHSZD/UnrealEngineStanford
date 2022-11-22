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

// The console main function is defined in sync()
void ASBullCowPrototype::sync() {
    FString base = "This is year ";
	constexpr int32 yearBook = 2022;
	base.Append(" ----------- ");
	base.Append(FString::FromInt(yearBook));
	UE_LOG(LogTemp, Log, TEXT("%s"), *base);

	bool bPlayAgain = false;

	
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
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
	const FString HIDDEN_WORD = "sober"; // this MUST be an ISOGRAM
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus ASBullCowPrototype::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an ISOGRAM
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


// receives a VALID guess, increments turn, and returns count
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
					BullCowCount.Bulls++; // increment bulls
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
	// treat 0 and 1 letter words as ISOGRAMS
	if (Word.Len() <= 1) { return true; }

	
	int length = Word.Len();
	int mapHash[26] = { 0 };

	// loop to store count of chars and check if it is
	// greater than 1
	for (int i = 0; i < length; i++) {
		mapHash[Word[i] - 'a']++;

		// if count > 1, return false
		if (mapHash[Word[i] - 'a'] > 1) {
			return false;
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









void ASBullCowPrototype::PrintIntro()
{
	FString base = "Welcome to Bulls and Cows, a fun word game. Can you guess the ISOGRAM I'm thinking of?";
	UE_LOG(LogTemp, Log, TEXT("%s"), *base);
	return;
}

// plays a single game to completion
void ASBullCowPrototype::PlayGame()
{
	ResetGame();
	int32 MaxTries = GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!IsGameWon() && GetCurrentTry() <= MaxTries) {
		FString Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = SubmitValidGuess(Guess);

		FString base = "Bulls = ";
		base.Append(FString::FromInt(BullCowCount.Bulls));
		UE_LOG(LogTemp, Log, TEXT("%s"), *base);

		base = "Cows = ";
		base.Append(FString::FromInt(BullCowCount.Cows));
		UE_LOG(LogTemp, Log, TEXT("%s"), *base);
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FString ASBullCowPrototype::GetValidGuess()
{
	FString Guess;
	FString base;
	int counter = 0;
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// get a guess from the player
		int32 CurrentTry = GetCurrentTry();
		base = "Try ";
		base.Append(FString::FromInt(CurrentTry));
		base.Append(" of ");
		base.Append(FString::FromInt(GetMaxTries()));
		base.Append(". Enter your guess: ");
		UE_LOG(LogTemp, Log, TEXT("%s"), *base);

		Guess = GuessList[counter++]; //std::getline(std::cin, Guess);
		UE_LOG(LogTemp, Log, TEXT("%s"), *Guess);
		// check status and give feedback
		Status = CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			base = "Please enter a ";
			base.Append(FString::FromInt(GetHiddenWordLength()));
			base.Append(" letter word.");
			UE_LOG(LogTemp, Log, TEXT("%s"), *base);
			break;
		case EGuessStatus::Not_Isogram:
			base = "Please enter a word without repeating letters.";
			UE_LOG(LogTemp, Log, TEXT("%s"), *base);
			break;
		case EGuessStatus::Not_Lowercase:
			base = "Please enter all lowercase letters.";
			UE_LOG(LogTemp, Log, TEXT("%s"), *base);
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool ASBullCowPrototype::AskToPlayAgain()
{
	FString base = "Do you want to play again with the same hidden word (y/n)? ";
	UE_LOG(LogTemp, Log, TEXT("%s"), *base);
	FString Response = "n"; //std::getline(std::cin, Response);
	UE_LOG(LogTemp, Log, TEXT("%s"), *Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void ASBullCowPrototype::PrintGameSummary()
{
	if (IsGameWon())
	{
		FString base = "WELL DONE - YOU WIN!";
		UE_LOG(LogTemp, Log, TEXT("%s"), *base);
	}
	else
	{
		FString base = "Better luck next time!";
		UE_LOG(LogTemp, Log, TEXT("%s"), *base);
	}
}