// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponClass.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponClass : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IWeaponClass
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    virtual void Attack();
    virtual void AerialAttack();
    virtual void ModeAttack();
    virtual void ModeAerialAttack();
    virtual void ForwardAttack();
    virtual void BackwardAttack();
    virtual void LeftwardAttack();
    virtual void RightwardAttack();
    virtual void AerialForwardAttack();
    virtual void AerialBackwardAttack();
    virtual void AerialLeftwardAttack();
    virtual void AerialRightwardAttack();
    virtual void ModeForwardAttack();
    virtual void ModeBackwardAttack();
    virtual void ModeLeftwardAttack();
    virtual void ModeRightwardAttack();
    virtual void ModeAerialForwardAttack();
    virtual void ModeAerialBackwardAttack();
    virtual void ModeAerialLeftwardAttack();
    virtual void ModeAerialRightwardAttack();
};
