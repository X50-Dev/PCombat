// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ComboDataAsset.h"
#include "AttackDataAsset.h"
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

void AMusoFighter::DoLowAttack()
{
	Attack("X");
}
void AMusoFighter::DoHeavyAttack()
{
	Attack("Y");
}

void AMusoFighter::Attack(FString Input)
{
	if (!ComboTree) return;

	CurrentCombo = UKismetStringLibrary::Concat_StrStr(CurrentCombo, Input);

	if (!ComboTree->Combos.Contains(CurrentCombo))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Invalid Combo: %s"), *CurrentCombo));
		ResetCombo();
		if (!ComboTree->Combos.Contains(Input))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Combo does not existe")));
			return;
		}
		CurrentCombo = UKismetStringLibrary::Concat_StrStr(CurrentCombo, Input);
	}

	UAttackDataAsset* Attack = ComboTree->Combos[CurrentCombo];
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%s"), *Attack->GetName()));
}


void AMusoFighter::ResetCombo() 
{
	CurrentCombo = "";
}
