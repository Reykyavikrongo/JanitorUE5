// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.h"
#include "GameFramework/Character.h"
#include "MarbleTeleport.h"
#include "Marbles.generated.h"

UCLASS()
class JANITORUE5_API AMarbles : public AActor, public IWeaponClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarbles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    AMarbleTeleport* TeleportMarble;
    AMarbleTeleport* UpwardsTeleportMarble;
    AMarbleTeleport* DownwardsTeleportMarble;

    bool TeleportExists = false;
    bool UpwardsTeleportExists = false;
    bool DownwardsTeleportExists = false;

    bool TeleportStopped = false;
    bool UpwardsTeleportStopped = false;
    bool DownwardsTeleportStopped = false;

    float TeleportTime;
    float UpwardsTeleportTime;
    float DownwardsTeleportTime;

public:	

    FTransform ProjectileTransform;

	virtual void Tick(float DeltaSeconds) override;

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
