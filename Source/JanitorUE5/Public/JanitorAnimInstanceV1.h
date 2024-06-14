// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "JanitorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JanitorAnimInstanceV1.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class JANITORUE5_API UJanitorAnimInstanceV1 : public UAnimInstance
{
	GENERATED_BODY()
public:
	UJanitorAnimInstanceV1();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
	bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
	bool isAlive;

	UPROPERTY(BlueprintReadOnly, Category = "Actor Pointer")
	AJanitorCharacter* Owner;

	UPROPERTY(BlueprintReadOnly, Category = "Character Movement Component")
	UCharacterMovementComponent* CharacterMovementComponent;

	void UpdateAnimProperties();
	
};
