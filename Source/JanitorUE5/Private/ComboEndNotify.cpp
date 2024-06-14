// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboEndNotify.h"
#include "JanitorCharacter.h"


void UComboEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
			janitor->ComboCounter = 0;
	}
}
