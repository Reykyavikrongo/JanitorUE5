// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ENUMS.h"
#include "BasicEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBasicEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JANITORUE5_API IBasicEnemyInterface
{
	GENERATED_BODY()

public:

	// functions for behaviour when hit
	virtual void GotHit(StatusEffect statusEffect) = 0;
	virtual void Stagger() = 0;
	virtual void AirStagger() = 0;
	virtual void KnockBack() = 0;
	virtual void KnockUp() = 0;
	virtual void Pull() = 0;
	virtual void KnockDown() = 0;
	virtual void KnockInPredeterminedDirection() = 0;

};
