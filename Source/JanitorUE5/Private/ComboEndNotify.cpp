// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboEndNotify.h"
#include "JanitorCharacter.h"
#include "ENUMS.h"


void UComboEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
		{
			janitor->setCurrentAnimTier(AnimationTier::Idle);
			janitor->ComboCounter = 0;
			
			TArray<UHurtBox*> meleeAndRangedArray;
			meleeAndRangedArray.Append(janitor->GetCurrentMeleeWeapon()->GetHurtBoxArray());
			meleeAndRangedArray.Append(janitor->GetCurrentRangedWeapon()->GetHurtBoxArray());
			for (int i = 0; i < meleeAndRangedArray.Num(); ++i)
			{
				meleeAndRangedArray[i]->SetCanBeActivated(false);
				meleeAndRangedArray[i]->SetActive(false);
				meleeAndRangedArray[i]->ClearAttackName();
			}
		}
	}
}
