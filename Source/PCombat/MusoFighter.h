// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PCombatCharacter.h"
#include "GameFramework/Character.h"
#include "MusoFighter.generated.h"

class UComboDataAsset;
UCLASS()
class PCOMBAT_API AMusoFighter : public APCombatCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMusoFighter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack(FString Input);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
