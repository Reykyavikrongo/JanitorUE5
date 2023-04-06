// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	SkeletalMesh->SetupAttachment(RootComponent);

	LockOnComponent->SetupAttachment(StaticMesh);
	LockOnComponent->SetText(FText::FromString(""));
	LockOnComponent->SetWorldSize(100);
	LockOnComponent->SetRelativeLocation(LockOnComponent->GetRelativeLocation() + FVector(0, 0, 100));

}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	LockOnComponent->SetRelativeRotation(CameraRotation.Add(180, 0, 180));

}

// Called to bind functionality to input
void ABasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}