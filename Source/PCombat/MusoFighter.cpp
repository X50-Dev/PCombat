// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ComboDataAsset.h"
#include "AttackDataAsset.h"
#include "MusoFighter.h"
#include "AN_ComboAttack.h"
#include "Kismet/KismetStringLibrary.h"

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
	DoAttack(ComboTree->Combos[CurrentCombo]);
}

void AMusoFighter::DoAttack(UAttackDataAsset* Attack) 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%s"), *Attack->GetName()));

	GetMesh()->PlayAnimation(Attack->Animation, false);

	const auto NotifyEvents = Attack->Animation->Notifies;
	for(FAnimNotifyEvent Event : NotifyEvents) 
	{
		if (const auto Notify = Cast<UAN_ComboAttack>(Event.Notify))
		{
			Notify->OnNotified.AddUObject(this, &AMusoFighter::ResetComboTimer);
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("No Combo Notify found")));
		}
	}
}

void AMusoFighter::ResetComboTimer() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Attack effected")));
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMusoFighter::ResetCombo, 0.7f, false);
}

void AMusoFighter::ResetCombo() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Combo reset")));
	CurrentCombo = "";
}
