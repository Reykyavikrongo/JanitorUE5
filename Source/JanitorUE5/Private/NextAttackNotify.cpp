// Fill out your copyright notice in the Description page of Project Settings.


#include "NextAttackNotify.h"
#include "JanitorCharacter.h"


void UNextAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
		{
			janitor->ComboCounter++;
			janitor->setCurrentAnimTier(AnimationTier::Attacking);
		}
	}
}
