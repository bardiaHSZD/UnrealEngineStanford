// Fill out your copyright notice in the Description page of Project Settings.


#include "SBullCowPrototype.h"

// Sets default values
ASBullCowPrototype::ASBullCowPrototype()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	UE_LOG(LogTemp, Log, TEXT("Hi World!"));
}