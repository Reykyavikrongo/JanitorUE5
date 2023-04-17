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

    UPROPERTY(VisibleAnywhere, Blueprintable, Category = StaticMesh)
    UStaticMeshComponent* MarblesMesh;

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

	void Tick(float DeltaSeconds) override;

	void Attack();
    void AerialAttack();
    void ModeAttack();
    void ModeAerialAttack();
    void ForwardAttack();
    void BackwardAttack();
    void LeftwardAttack();
    void RightwardAttack();
    void AerialForwardAttack();
    void AerialBackwardAttack();
    void AerialLeftwardAttack();
    void AerialRightwardAttack();
    void ModeForwardAttack();
    void ModeBackwardAttack();
    void ModeLeftwardAttack();
    void ModeRightwardAttack();
    void ModeAerialForwardAttack();
    void ModeAerialBackwardAttack();
    void ModeAerialLeftwardAttack();
    void ModeAerialRightwardAttack();
    UStaticMeshComponent* GetMesh();


};
