// Fill out your copyright notice in the Description page of Project Settings.


#include "Marbles.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "JanitorCharacter.h"

// Sets default values
AMarbles::AMarbles()
{
	janitor = Cast<AJanitorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MarblesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MarblesMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> marblesMeshAsset(TEXT("StaticMesh'/Game/Weapons/marble/bag/sac.sac'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> marblesMaterialAsset(TEXT("StaticMesh'/Game/Weapons/marble/bag/purrpl_velvet.purrpl_velvet'"));
	MarblesMesh->SetMaterial(0, marblesMaterialAsset.Object);

	if (marblesMeshAsset.Object)
	{
		MarblesMesh->SetStaticMesh(marblesMeshAsset.Object);
	}

	MarblesMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MarblesMesh->AddRelativeLocation(FVector(-6.0, -10.0, 2));
	MarblesMesh->AddRelativeRotation(FRotator(105.0, 30.0, 180.0));
	MarblesMesh->SetWorldScale3D(FVector(0.4, 0.4, 0.4));
}	

// Called when the game starts or when spawned
void AMarbles::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMarbles::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (!TeleportExists && TeleportTime != 0.0f)
		TeleportTime = 0.0f;
	if (TeleportExists && !TeleportStopped)
	{
		TeleportTime += DeltaSeconds;
		if (TeleportTime >= 1)
			this->ModeAttack();
	}
}

void AMarbles::Attack()
{
	// e&i shot
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Attack pressed"));
	return;
}

void AMarbles::AerialAttack()
{
	// e&i shot
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Aerial Attack pressed"));
	return;
}

void AMarbles::ModeAttack()
{
	if (!TeleportExists)
	{
		TeleportExists = true;
		FRotator Rotation;
		FActorSpawnParameters SpawnInfo;
		// forward teleport marble gets shot out

		if (janitor->GetIsLockedOn())
			ProjectileTransform = janitor->getLockOnArrow()->GetComponentTransform();
		else
			ProjectileTransform = janitor->getFollowArrow()->GetComponentTransform();
		
		TeleportMarble = GetWorld()->SpawnActor<AMarbleTeleport>(AMarbleTeleport::StaticClass(), ProjectileTransform, SpawnInfo);
		
	}
	else if (TeleportExists && !TeleportStopped)
	{
		TeleportStopped = true;
		TeleportMarble->PMComponent->StopMovementImmediately();
	}
	else
	{
		TeleportExists = false;
		TeleportStopped = false;
		FVector MarbleLocation = TeleportMarble->GetActorLocation();
		TeleportMarble->Destroy();
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(MarbleLocation);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Attack pressed"));
	return;
}

void AMarbles::ModeAerialAttack()
{
	// forward teleport marble gets shot out
	ModeAttack();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Aerial Attack pressed"));
	return;
}

void AMarbles::ForwardAttack()
{
	// 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Forward Attack pressed"));
	return;
}

void AMarbles::BackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Backward Attack pressed"));
	return;
}

void AMarbles::LeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Leftward Attack pressed"));
	return;
}

void AMarbles::RightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Rightward Attack pressed"));
	return;
}

void AMarbles::AerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Aerial Forward Attack pressed"));
	return;
}

void AMarbles::AerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Aerial Backward Attack pressed"));
	return;
}

void AMarbles::AerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Aerial Leftward Attack pressed"));
	return;
}

void AMarbles::AerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Aerial Rightward Attack pressed"));
	return;
}

void AMarbles::ModeForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Forward Attack pressed"));
	return;
}

void AMarbles::ModeBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Backward Attack pressed"));
	return;
}

void AMarbles::ModeLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Leftward Attack pressed"));
	return;
}

void AMarbles::ModeRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Rightward Attack pressed"));
	return;
}

void AMarbles::ModeAerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Aerial Forward Attack pressed"));
	return;
}

void AMarbles::ModeAerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Aerial Backward Attack pressed"));
	return;
}

void AMarbles::ModeAerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Aerial Leftward Attack pressed"));
	return;
}

void AMarbles::ModeAerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Marbles) Mode Aerial Rightward Attack pressed"));
	return;
}

UStaticMeshComponent* AMarbles::GetMesh()
{
	return MarblesMesh;
}