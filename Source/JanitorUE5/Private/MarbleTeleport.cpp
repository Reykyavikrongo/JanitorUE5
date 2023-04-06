// Fill out your copyright notice in the Description page of Project Settings.


#include "MarbleTeleport.h"

// Sets default values
AMarbleTeleport::AMarbleTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> BaseMeshMaterial(TEXT("StaticMesh'/Game/StarterContent/Props/Materials/M_MaterialSphere.M_MaterialSphere'"));
	StaticMesh->SetMaterial(0, BaseMeshMaterial.Object);
	StaticMesh->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	StaticMesh->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(StaticMesh);
	ParticleComponent->bAutoActivate = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BaseParticleAsset(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));

	PMComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	PMComponent->InitialSpeed = 1500.0f;
	PMComponent->bShouldBounce = true;
	PMComponent->MaxSpeed = 1500.0f;
	PMComponent->ProjectileGravityScale = 0.0f;
	PMComponent->Bounciness = 1.0f;

	if (BaseParticleAsset.Object)
	{
		ParticleComponent->SetTemplate(BaseParticleAsset.Object);
	}

	if (BaseMeshAsset.Object)
	{
		StaticMesh->SetStaticMesh(BaseMeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void AMarbleTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarbleTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

