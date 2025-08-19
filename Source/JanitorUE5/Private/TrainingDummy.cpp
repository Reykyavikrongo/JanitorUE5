// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingDummy.h"

ATrainingDummy::ATrainingDummy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	SkeletalMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	SkeletalMesh->SetupAttachment(StaticMesh);	 // it has to be setup to the static mesh because it is inherited from ALockOnablePawn which has a staticmesh setup on its root component
	
	m_HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	m_HitBox->SetupAttachment(StaticMesh);
	m_HitBox->SetHiddenInGame(false);
	m_HitBox->SetVisibility(true);
	m_HitBox->SetMobility(EComponentMobility::Movable);
	m_HitBox->SetRelativeScale3D(FVector(1.0, 0.52, 2.9));
	m_HitBox->SetRelativeLocation(FVector(0, 0, 91));

	ConstructorHelpers::FObjectFinder<UAnimMontage> staggerAnimObject(TEXT("/Script/Engine.AnimMontage'/Game/Enemies/TrainingDummy/Animations/training_dummy_stagger_recovery_Montage.training_dummy_stagger_recovery_Montage'"));
	staggerAnim = staggerAnimObject.Object;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("huh"));
	//if (!staggerAnim)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("anim failed"));
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("anim succ"));

	//}
	static ConstructorHelpers::FClassFinder<UAnimInstance> DummyAnimBPClass(TEXT("/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny_C"));
	if (DummyAnimBPClass.Succeeded())
	{
		SkeletalMesh->SetAnimInstanceClass(DummyAnimBPClass.Class);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("couldn't find dummy anim class"));
	}

	bHurtBoxIsOverlapped = false;
	bIsOnHitCooldown = false;
}

void ATrainingDummy::BeginPlay()
{
	Super::BeginPlay();

	if (!staggerAnim)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Anim is NULL"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("anim success"));
	}

	m_HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::OnBeginOverlapBox);
	m_HitBox->OnComponentEndOverlap.AddDynamic(this, &ABasicEnemy::OnEndOverlapBox);
}

void ATrainingDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrainingDummy::GotHit(StatusEffect statusEffect)
{
	Super::GotHit(statusEffect);
}

void ATrainingDummy::Stagger()
{
	Super::Stagger();
	if (staggerAnim)
	{
		if (SkeletalMesh)
		{
			if (SkeletalMesh->GetAnimInstance())
			{
				SkeletalMesh->GetAnimInstance()->Montage_Play(staggerAnim);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("THE ANIMATION SHOULD HAVE PLAYED"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("NO ANIM INSTANCE FOR SKELETAL MESH DUMMY"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("NO SKELETAL MESH DUMMY"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("NOANIMATIONFORDUMMY"));
	}
}

void ATrainingDummy::AirStagger()
{
	Super::AirStagger();
}

void ATrainingDummy::KnockBack()
{
	Super::KnockBack();
}

void ATrainingDummy::KnockUp()
{
	Super::KnockUp();
}

void ATrainingDummy::Pull()
{
	Super::Pull();
}

void ATrainingDummy::KnockDown()
{
	Super::KnockDown();
}

void ATrainingDummy::KnockInPredeterminedDirection()
{
	Super::KnockInPredeterminedDirection();
}

void ATrainingDummy::OnBeginOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlapBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATrainingDummy::OnEndOverlapBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlapBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

