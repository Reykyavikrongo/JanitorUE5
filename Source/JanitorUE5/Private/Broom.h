// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.h"
#include "WeaponClassBufferImplementor.h"
#include "GameFramework/Character.h"
#include "Broom.generated.h"

UCLASS()
class JANITORUE5_API ABroom : public AWeaponClassBufferImplementor//public AActor, public IWeaponClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABroom();

    // 
    UPROPERTY(VisibleAnywhere, Blueprintable, Category = StaticMesh)
    UStaticMeshComponent* BroomMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
    UAnimMontage* FirstGroundAttackMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void Attack() override;
    void AerialAttack() override;
    void ModeAttack() override;
    void ModeAerialAttack() override;
    void ForwardAttack() override;
    void BackwardAttack() override;
    void LeftwardAttack() override;
    void RightwardAttack() override;
    void AerialForwardAttack() override;
    void AerialBackwardAttack() override;
    void AerialLeftwardAttack() override;
    void AerialRightwardAttack() override;
    void ModeForwardAttack() override;
    void ModeBackwardAttack() override;
    void ModeLeftwardAttack() override;
    void ModeRightwardAttack() override;
    void ModeAerialForwardAttack() override;
    void ModeAerialBackwardAttack() override;
    void ModeAerialLeftwardAttack() override;
    void ModeAerialRightwardAttack() override;
    UStaticMeshComponent* GetMesh() override;
};
