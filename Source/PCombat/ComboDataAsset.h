// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ComboDataAsset.generated.h"

class UAttackDataAsset;
/**
 * 
 */
UCLASS()
class PCOMBAT_API UComboDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	TMap<FString, UAttackDataAsset*> Combos;
};
