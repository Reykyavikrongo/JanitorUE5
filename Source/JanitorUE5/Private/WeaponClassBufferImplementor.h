// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.h"
#include "HurtBox.h"
#include "WeaponClassBufferImplementor.generated.h"

class AJanitorCharacter;

UCLASS()
class AWeaponClassBufferImplementor : public AActor, public IWeaponClass
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AWeaponClassBufferImplementor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AJanitorCharacter* janitor;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
    TArray<UHurtBox*> m_HurtBoxArr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


    virtual void Attack() override;
    virtual void AerialAttack() override;
    virtual void ModeAttack() override;
    virtual void ModeAerialAttack() override;
    virtual void ForwardAttack() override;
    virtual void BackwardAttack() override;
    virtual void LeftwardAttack() override;
    virtual void RightwardAttack() override;
    virtual void AerialForwardAttack() override;
    virtual void AerialBackwardAttack() override;
    virtual void AerialLeftwardAttack() override;
    virtual void AerialRightwardAttack() override;
    virtual void ModeForwardAttack() override;
    virtual void ModeBackwardAttack() override;
    virtual void ModeLeftwardAttack() override;
    virtual void ModeRightwardAttack() override;
    virtual void ModeAerialForwardAttack() override;
    virtual void ModeAerialBackwardAttack() override;
    virtual void ModeAerialLeftwardAttack() override;
    virtual void ModeAerialRightwardAttack() override;
    virtual UStaticMeshComponent* GetMesh() override;
    UFUNCTION()
    virtual void DoAttack(DirectionENUM Direction) override;
    UFUNCTION()
    virtual void DoModeAttack(DirectionENUM Direction) override;

    TArray<UHurtBox*> GetHurtBoxArray();
};
