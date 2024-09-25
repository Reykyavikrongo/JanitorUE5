// Fill out your copyright notice in the Description page of Project Settings.


#include "Broom.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "HurtBox.h"
#include "JanitorCharacter.h"

// Sets default values
ABroom::ABroom()
{
	janitor = Cast<AJanitorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	BroomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BroomMesh->SetupAttachment(RootComponent);

	//Setting the animations
	ConstructorHelpers::FObjectFinder<UAnimMontage> BroomGroundAttackMontage(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Janitor/CombatAnimations/Montages/broom_combo_1.broom_combo_1'"));
	FirstGroundAttackMontage = BroomGroundAttackMontage.Object;
	

	// notice the static keyword is missing here, for future reference it made the wrong mesh be loaded in because i used a placeholder mesh before the actual one i wanted, this is caused by either the VS compiler or the static keyword or the fact that this is the only private classed weapon. idk
	ConstructorHelpers::FObjectFinder<UStaticMesh> BroomMeshAsset(TEXT("StaticMesh'/Game/Weapons/Broom/broom5/broom_01.broom_01'"));
	ConstructorHelpers::FObjectFinder<UMaterial> BroomMaterial(TEXT("Material'/Game/Weapons/Broom/broom5/broom_material.broom_material'"));

	BroomMesh->SetMaterial(0, BroomMaterial.Object);

	if (BroomMeshAsset.Object)
	{
		BroomMesh->SetStaticMesh(BroomMeshAsset.Object);
	}

	BroomMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BroomMesh->SetMobility(EComponentMobility::Movable); 
	BroomMesh->AddRelativeLocation(FVector(0.0, 0.0, 130.0));
	BroomMesh->AddRelativeRotation(FRotator(180.0, 0.0, 0.0));
	BroomMesh->SetWorldScale3D(FVector(0.58, 0.58, 0.58));

	m_HurtBoxBrush = CreateDefaultSubobject<UHurtBox>(TEXT("HurtBox"));
	m_HurtBoxBrush->SetupAttachment(BroomMesh);
	m_HurtBoxBrush->SetMobility(EComponentMobility::Movable);
	m_HurtBoxBrush->SetHiddenInGame(false);
	m_HurtBoxBrush->SetVisibility(true);
	m_HurtBoxBrush->SetRelativeScale3D(FVector(0.8, 0.4, 2.5));
	m_HurtBoxBrush->SetRelativeLocation(FVector(-1, 0, 70));

	m_HurtBoxArr.Add(m_HurtBoxBrush);

}

// Called when the game starts or when spawned
void ABroom::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStaticMeshComponent* ABroom::GetMesh()
{
	return BroomMesh;
}

void ABroom::Attack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Attack pressed"));
	if (FirstGroundAttackMontage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("animation valid (broom)"));
		m_HurtBoxBrush->SetStatusEffect(StatusEffect::KnockUp);
		m_HurtBoxBrush->SetCanBeActivated(true);
		m_HurtBoxBrush->SetAttackName("GroundBroom_1");
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->PlayAnimMontage(FirstGroundAttackMontage, 1, NAME_None);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("NO ANIMATION LOADED"));
	}
		
	return;
}

void ABroom::AerialAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Aerial Attack pressed"));
	return;
}

void ABroom::ModeAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Attack pressed"));
	return;
}

void ABroom::ModeAerialAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Aerial Attack pressed"));
	return;
}

void ABroom::ForwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Forward Attack pressed"));
	return;
}

void ABroom::BackwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Backward Attack pressed"));
	return;
}

void ABroom::LeftwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Leftward Attack pressed"));
	return;
}

void ABroom::RightwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Rightward Attack pressed"));
	return;
}

void ABroom::AerialForwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Aerial Forward Attack pressed"));
	return;
}

void ABroom::AerialBackwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Aerial BackwardAttack pressed"));
	return;
}

void ABroom::AerialLeftwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Aerial Leftward Attack pressed"));
	return;
}

void ABroom::AerialRightwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Aerial Rightward Attack pressed"));
	return;
}

void ABroom::ModeForwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Forward Attack pressed"));
	return;
}

void ABroom::ModeBackwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Backward Attack pressed"));
	return;
}

void ABroom::ModeLeftwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Leftward Attack pressed"));
	return;
}

void ABroom::ModeRightwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode RightwardAttack pressed"));
	return;
}

void ABroom::ModeAerialForwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Aerial Forward Attack pressed"));
	return;
}

void ABroom::ModeAerialBackwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Aerial Backward Attack pressed"));
	return;
}

void ABroom::ModeAerialLeftwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Aerial Leftward Attack pressed"));
	return;
}

void ABroom::ModeAerialRightwardAttack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Mode Aerial Rightward Attack pressed"));
	return;
}
