// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackDataAsset.generated.h"
/**
 * 
 */
UCLASS()
class PCOMBAT_API UAttackDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	UAnimSequence* Animation;
};
