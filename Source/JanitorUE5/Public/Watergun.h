// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.h"
#include "Watergun.generated.h"

UCLASS()
class JANITORUE5_API AWatergun : public AActor, public IWeaponClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWatergun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
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
