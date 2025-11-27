#pragma once

#include "CoreMinimal.h"
#include "PCombatCharacter.h"
#include "GameFramework/Character.h"
#include "MusoFighter.generated.h"

class UComboDataAsset;
class UAttackDataAsset;
UCLASS()
class PCOMBAT_API AMusoFighter : public APCombatCharacter
{
	GENERATED_BODY()

public:
	AMusoFighter();

protected:
	virtual void BeginPlay() override;

	void Attack();

	void DoAttack(UAttackDataAsset* Attack);
	void ResetCombo();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAttackFinished();

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* HeavyAttackAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LowAttackAction;

protected:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoLowAttack();
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoHeavyAttack();

public:
	UPROPERTY(EditAnywhere, Category = "Variable")
	UComboDataAsset* ComboTree;
	UPROPERTY(EditAnywhere, Category = "Variable")
	float TimerCount;
private:
	FTimerHandle ComboTimer;
	FString InputAttack;
	FString CurrentCombo;
	bool bBufferAttack;
	bool bOnAttack;
};
