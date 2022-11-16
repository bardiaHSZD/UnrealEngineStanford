// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UNREALENGINESTANFORD_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// The collision component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	// We assign a velocity and it goes on a straight line
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	// To have something to show in the world environment
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
