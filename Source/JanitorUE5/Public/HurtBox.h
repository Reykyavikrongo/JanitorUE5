// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "ENUMS.h"
#include "HurtBox.generated.h"

/**
 * 
 */
UCLASS()
class JANITORUE5_API UHurtBox : public UBoxComponent
{
	GENERATED_BODY()

private:
	StatusEffect m_StatusEffect;
	bool bIsActive; // bool that says if the hurtbox should apply it's effects
	bool bCanBeActivated; // bool to confirm which hurtboxes can be activated during the "isActive" interval (useful if multiple hurtboxes will be activated)
	//getter i setter fale
	int m_StatusDelay;

	FName m_AttackName;


public:
	UHurtBox();
	~UHurtBox();

	bool GetIsActive() const;
	void SetIsActive(bool newIsActive);

	bool GetCanBeActivated() const;
	void SetCanBeActivated(bool newCanBeActivated);

	StatusEffect GetStatusEffect();
	void SetStatusEffect(StatusEffect newStatusEffect);

	FName GetAttackName() const;
	void SetAttackName(FName NewAttackName);
	void ClearAttackName();

};
