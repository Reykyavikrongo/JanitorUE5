// Fill out your copyright notice in the Description page of Project Settings.


#include "JanitorAnimInstanceV1.h"


UJanitorAnimInstanceV1::UJanitorAnimInstanceV1()
{
	Speed = 0.f;

	if (!Owner)
	{
		

	}
}

void UJanitorAnimInstanceV1::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner)
		UpdateAnimProperties();
}

void UJanitorAnimInstanceV1::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AJanitorCharacter>(TryGetPawnOwner());


}

void UJanitorAnimInstanceV1::UpdateAnimProperties()
{
	Speed = Owner->GetVelocity().Size();

}
