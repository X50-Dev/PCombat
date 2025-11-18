// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ComboDataAsset.h"
#include "MusoFighter.h"
#include <Kismet/KismetStringLibrary.h>

// Sets default values
AMusoFighter::AMusoFighter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMusoFighter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusoFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMusoFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast sécurisé vers UEnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LowAttackAction, ETriggerEvent::Started, this, &AMusoFighter::DoLowAttack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Started, this, &AMusoFighter::DoHeavyAttack);
	}
}


