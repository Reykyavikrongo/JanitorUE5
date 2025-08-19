// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LockOnablePawn.h"
#include "ENUMS.h"
#include "Animation/AnimMontage.h"
#include "BasicEnemyInterface.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.generated.h"

/**
 * 
 */
 //TODO: Create an interface for basic enemy so it can be inherited, interface should be generated within UE
UCLASS()
class JANITORUE5_API ABasicEnemy : public ALockOnablePawn, public IBasicEnemyInterface
{
	GENERATED_BODY()

public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	//UAnimMontage* launch;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	//UAnimMontage* stagger;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	//UAnimMontage* staggerRecovery;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* m_HitBox;

	bool bHurtBoxIsOverlapped;

	// used so the enemy knows what it is being hit by etc. 
	// HACK: might cause issues if there are 2 or more hurtboxes overlapping at once as the newer one will override the previous one
	class UHurtBox* m_HurtBoxOfJanitorWeapon;

	bool bIsOnHitCooldown;

	// Sets default values for this pawn's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* staggerAnim;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	// functions for behaviour when hit
	virtual void GotHit(StatusEffect statusEffect) override;
	virtual void Stagger() override;
	virtual void AirStagger() override;
	virtual void KnockBack() override;
	virtual void KnockUp() override;
	virtual void Pull() override;
	virtual void KnockDown() override;
	virtual void KnockInPredeterminedDirection() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnBeginOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
