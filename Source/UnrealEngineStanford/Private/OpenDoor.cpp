// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	FString PlayerName = ActorThatOpens->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is the first player controller here"), *PlayerName);

}

void UOpenDoor::OpenTheDoor()
{
	Owner = GetOwner();
	FRotator NewRotation = FRotator(0.f, -OpenAngle, 0.f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("Problem in %s"), *GetOwner()->GetName())
	}
	else {
		FString PressureName = PressurePlate->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is the first player controller here and the trigger volume is %s"), *GetOwner()->GetName(), *PressureName);
	}
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenTheDoor();
	}
}

