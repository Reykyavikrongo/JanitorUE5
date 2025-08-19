// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayAnimTestNotify.h"
#include "JanitorCharacter.h"
#include "ENUMS.h"

//TODO: make this a general implementation instead of hard coded, each attack will have its own recovery anim, probably use templates

void UPlayAnimTestNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AJanitorCharacter* janitor = Cast<AJanitorCharacter>(MeshComp->GetOwner());
		if (janitor)
		{
			//ABroom* broom;
			//broom = Cast<ABroom>(janitor->GetCurrentMeleeWeapon());
			////janitor->StopAnimMontage();
			//janitor->PlayAnimMontage(broom->branch2_recovery, 1, NAME_None);
			//janitor->setCurrentAnimTier(AnimationTier::Idle);

			// NEW GENERELIZED CODE FOR THIS

			if (janitor->getCurrentAnimationWeapon())
			{
				AWeaponClassBufferImplementor* weapon = janitor->getCurrentAnimationWeapon();
				if (weapon->getRecoveryMontage())
				{
					UAnimMontage* recoveryAnimation = weapon->getRecoveryMontage();
					janitor->PlayAnimMontage(recoveryAnimation, 1, NAME_None);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString(TEXT("no recovery montage")));
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString(TEXT("no currentAnimationWeapon")));
			}
			janitor->setCurrentAnimTier(AnimationTier::Idle);

		}
	}
}