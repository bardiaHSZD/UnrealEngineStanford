// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBullCowPrototype.generated.h"


// to make syntax Unreal friendly

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};




UCLASS()
class UNREALENGINESTANFORD_API ASBullCowPrototype : public AActor
{
	GENERATED_BODY()
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	std::vector<FString> GuessList{ "sobbe", "soberia", "rebos", "bores", "sbore",
		"sobre", "erbos", "bosre", "bores", "serob", "seorb", "srbeo", "beors", "srebo", "sober" };
	std::vector<FString> PlayAgainList{ "y", "n"};
	int counter = 0;
	int tryCounter = 0;


public:	
	// Sets default values for this actor's properties
	ASBullCowPrototype();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void ResetGame();
	FBullCowCount SubmitValidGuess(FString);

	void PrintIntro();
	void PlayTheGame();
	FString GetValidGuess();
	bool AskToPlayAgain();
	void PrintGameSummary();




protected:
	void sync();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
