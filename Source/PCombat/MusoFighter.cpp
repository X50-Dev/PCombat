#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ComboDataAsset.h"
#include "AttackDataAsset.h"
#include "MusoFighter.h"
#include "AN_ComboAttack.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

AMusoFighter::AMusoFighter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMusoFighter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusoFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bBufferAttack && !bOnAttack) Attack(InputAttack);
}

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
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		InputAttack = "X";
		bBufferAttack = true;
	}	
}
void AMusoFighter::DoHeavyAttack()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		InputAttack = "Y";
		bBufferAttack = true;
	}
}

void AMusoFighter::Attack(FString Input)
{
	if (!ComboTree) return;

	bBufferAttack = false;
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
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (!Attack->Animation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("No Attack found")));
		return;
	}
	bOnAttack = true;

	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	AnimInstance->PlaySlotAnimationAsDynamicMontage(Attack->Animation,
		FName("DefaultSlot"), 0.1f, 0.1f, 1.0f, 1.0f, -1.0f);

	GetWorldTimerManager().ClearAllTimersForObject(this);
	//GetWorldTimerManager().SetTimer(ComboTimer, this, &AMusoFighter::ResetCombo, 0.0f, false);
	const auto NotifyEvents = Attack->Animation->Notifies;
	for (FAnimNotifyEvent Event : NotifyEvents)
	{
		if (const auto Notify = Cast<UAN_ComboAttack>(Event.Notify))
		{
			return;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("ERROR : No Combo Notify found")));
	bOnAttack = false;
}

void AMusoFighter::ResetComboTimer() 
{
	bOnAttack = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Attack effected")));
	GetWorldTimerManager().SetTimer(ComboTimer, this, &AMusoFighter::ResetCombo, 0.7f, false);
}

void AMusoFighter::ResetCombo() 
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Combo reset")));
	CurrentCombo = "";
}