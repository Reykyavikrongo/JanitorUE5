// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"
#include "Components/BoxComponent.h"
#include "HurtBox.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	SkeletalMesh->SetupAttachment(StaticMesh); // it has to be setup to the static mesh because it is inherited from ALockOnablePawn which has a staticmesh setup on its root component
	/*
	LockOnComponent->SetupAttachment(StaticMesh);
	LockOnComponent->SetText(FText::FromString(""));
	LockOnComponent->SetWorldSize(100);
	LockOnComponent->SetRelativeLocation(LockOnComponent->GetRelativeLocation() + FVector(0, 0, 100));
	*/
	m_HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	m_HitBox->SetupAttachment(StaticMesh);
	m_HitBox->SetHiddenInGame(false);
	m_HitBox->SetVisibility(true);
	m_HitBox->SetMobility(EComponentMobility::Movable);
	m_HitBox->SetRelativeScale3D(FVector(1.0, 0.52, 2.9));
	m_HitBox->SetRelativeLocation(FVector(0, 0, 91));

	bHurtBoxIsOverlapped = false;
	bIsOnHitCooldown = false;
	//m_HurtBoxOfJanitorWeapon = CreateDefaultSubobject<UHurtBox>(TEXT("HurtBox"));
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();

	m_HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::OnBeginOverlapBox);
	m_HitBox->OnComponentEndOverlap.AddDynamic(this, &ABasicEnemy::OnEndOverlapBox);
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	LockOnComponent->SetRelativeRotation(CameraRotation.Add(180, 0, 180));

	if (bHurtBoxIsOverlapped)
	{
		if (m_HurtBoxOfJanitorWeapon->GetIsActive())
		{
			if (!bIsOnHitCooldown)
			{
				bIsOnHitCooldown = true;
				GotHit(m_HurtBoxOfJanitorWeapon->GetStatusEffect());
			}
		}
		else
		{
			bIsOnHitCooldown = false;
		}
	}

}

// Called to bind functionality to input
void ABasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

void ABasicEnemy::GotHit(StatusEffect statusEffect)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("ENEMY GOT HIT"));
	switch (statusEffect) 
	{
		case(StatusEffect::Stagger):
			Stagger();
			break;
		case(StatusEffect::AirStagger):
			AirStagger();
			break;
		case(StatusEffect::KnockBack):
			KnockBack();
			break;
		case(StatusEffect::KnockUp):
			KnockUp();
			break;
		case(StatusEffect::Pull):
			Pull();
			break;
		case(StatusEffect::KnockDown):
			KnockDown();
			break;
		case(StatusEffect::KnockInPredeterminedDirection):
			KnockInPredeterminedDirection();
			break;
	}
}


void ABasicEnemy::Stagger()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("StaggerTriggered"));
}

void ABasicEnemy::AirStagger()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("AirStaggerTriggered"));
}

void ABasicEnemy::KnockBack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("KnockBackTriggered"));
}

void ABasicEnemy::KnockUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("KnockUpTriggered"));
}

void ABasicEnemy::KnockDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("KnockDownTriggered"));
}

void ABasicEnemy::Pull()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("PullTriggered"));
}

void ABasicEnemy::KnockInPredeterminedDirection()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("KnockInPredeterminedDirection"));
}

void ABasicEnemy::OnBeginOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsA(UHurtBox::StaticClass()))
	{
		m_HurtBoxOfJanitorWeapon = Cast<UHurtBox>(OtherComp);
		bHurtBoxIsOverlapped = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("OnBeginOverlapBasicEnemy"));
	}
	
}

void ABasicEnemy::OnEndOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//might not be useful idk
	bHurtBoxIsOverlapped = false;
	bIsOnHitCooldown = false;
	m_HurtBoxOfJanitorWeapon = nullptr;
}
