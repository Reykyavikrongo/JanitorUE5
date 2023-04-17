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

    // Static mesh for the weapon
    UPROPERTY(VisibleAnywhere, Blueprintable, Category = StaticMesh)
    UStaticMeshComponent* WaterGunMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void Tick(float DeltaTime) override;
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
