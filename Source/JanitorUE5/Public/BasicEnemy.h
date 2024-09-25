// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LockOnablePawn.h"
#include "ENUMS.h"
#include "BasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class JANITORUE5_API ABasicEnemy : public ALockOnablePawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* m_HitBox;

	// used so the enemy knows what it is being hit by etc. 
	// HACK: might cause issues if there are 2 or more hurtboxes overlapping at once as the newer one will override the previous one
	class UHurtBox* m_HurtBoxOfJanitorWeapon;

	bool bHurtBoxIsOverlapped;

	bool bIsOnHitCooldown;

public:
	// Sets default values for this pawn's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	// functions for behaviour when hit
	void GotHit(StatusEffect statusEffect);
	void Stagger();
	void AirStagger();
	void KnockBack();
	void KnockUp();
	void Pull();
	void KnockDown();
	void KnockInPredeterminedDirection();

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
