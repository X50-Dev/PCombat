// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ComboAttack.h"
#include "MusoFighter.h"

void UAN_ComboAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	AMusoFighter* MusoFighter = Cast<AMusoFighter>(MeshComp->GetOwner());
	if(MusoFighter)
	MusoFighter->ResetComboTimer();
}