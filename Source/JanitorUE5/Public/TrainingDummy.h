// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "TrainingDummy.generated.h"

/**
 * 
 */
UCLASS()
class JANITORUE5_API ATrainingDummy : public ABasicEnemy
{
	GENERATED_BODY()
public:
	ATrainingDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GotHit(StatusEffect statusEffect) override;
	virtual void Stagger() override;
	virtual void AirStagger() override;
	virtual void KnockBack() override;
	virtual void KnockUp() override;
	virtual void Pull() override;
	virtual void KnockDown() override;
	virtual void KnockInPredeterminedDirection() override;

	virtual void OnBeginOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnEndOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
