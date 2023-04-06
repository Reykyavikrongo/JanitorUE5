// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnablePawn.h"
#include "Components/WidgetComponent.h"
#include "Internationalization/Text.h"

// Sets default values
ALockOnablePawn::ALockOnablePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	LockOnComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LockOn"));
	LockOnComponent->SetupAttachment(StaticMesh);
	LockOnComponent->SetText(FText::FromString(""));
	LockOnComponent->SetWorldSize(100);
	LockOnComponent->SetRelativeLocation(LockOnComponent->GetRelativeLocation() + FVector(0, 0, 100));

}

// Called when the game starts or when spawned
void ALockOnablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALockOnablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	LockOnComponent->SetRelativeRotation(CameraRotation.Add(180, 0, 180));

}

// Called to bind functionality to input
void ALockOnablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

