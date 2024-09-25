// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HurtBoxAnimNotifyState.generated.h"

class UHurtBox;

/**
 * 
 */
UCLASS()
class JANITORUE5_API UHurtBoxAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY()
 	TArray<UHurtBox*> meleeAndRangedArray;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
