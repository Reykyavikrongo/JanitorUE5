// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MarbleTeleport.generated.h"

UCLASS()
class JANITORUE5_API AMarbleTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarbleTeleport();

	UPROPERTY(VisibleAnywhere, Blueprintable, Category = StaticMesh)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Blueprintable, Category = particles)
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(VisibleAnywhere, Blueprintable, Category = ProjectileMovement)
	UProjectileMovementComponent* PMComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
