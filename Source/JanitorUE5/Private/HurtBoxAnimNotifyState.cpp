// Fill out your copyright notice in the Description page of Project Settings.


#include "HurtBoxAnimNotifyState.h"
#include "HurtBox.h"
#include "JanitorCharacter.h"

void UHurtBoxAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("HurtBoxActivated"));
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
		{
			meleeAndRangedArray.Append(janitor->GetCurrentMeleeWeapon()->GetHurtBoxArray());
			meleeAndRangedArray.Append(janitor->GetCurrentRangedWeapon()->GetHurtBoxArray());
			for (int i = 0; i < meleeAndRangedArray.Num(); ++i)
			{
				if (meleeAndRangedArray.IsValidIndex(i))
				{
					if (meleeAndRangedArray[i]->GetCanBeActivated())
					{
						meleeAndRangedArray[i]->SetIsActive(true);
					}
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("MeleeAndRangedArray is empty"));
				}
			}
		}
	}
}

void UHurtBoxAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("HurtBoxDeactivated"));
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
		{
			for (int i = 0; i < meleeAndRangedArray.Num(); ++i)
			{
				if (meleeAndRangedArray.IsValidIndex(i))
				{
					meleeAndRangedArray[i]->SetIsActive(false);
				}
				else 
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("MeleeAndRangedArray is empty"));
				}
			}
			meleeAndRangedArray.Empty();
		}
	}
}

