// Fill out your copyright notice in the Description page of Project Settings.


#include "Skateboard.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "JanitorCharacter.h"

// Sets default values
ASkateboard::ASkateboard()
{
	janitor = Cast<AJanitorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Montage for high kick
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HighKickMontage(TEXT("AnimMontage'/Game/Characters/Mannequins/Animations/Quinn/MyAnimations/cascadeur/montages/high_kick_montage.high_kick_montage'"));
	FirstAttackMontage = HighKickMontage.Object;

	SkateboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SkateboardMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SkateboardMeshAsset(TEXT("StaticMesh'/Game/Weapons/skateboard/1/skateboard.skateboard'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardBearing1Material(TEXT("Material'/Game/Weapons/skateboard/1/Bearings1.Bearings1'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardBearing2Material(TEXT("Material'/Game/Weapons/skateboard/1/Bearings2.Bearings2'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardWheelMaterial(TEXT("Material'/Game/Weapons/skateboard/1/Wheels.Wheels'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardBoltsMaterial(TEXT("Material'/Game/Weapons/skateboard/1/bolts.bolts'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardGripMaterial(TEXT("Material'/Game/Weapons/skateboard/1/Grip.Grip'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardDeckBottomMaterial(TEXT("Material'/Game/Weapons/skateboard/1/Deck_Bottom.Deck_Bottom'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardSideMaterial(TEXT("Material'/Game/Weapons/skateboard/1/Deck_Side.Deck_Side'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SkateboardTrucksMaterial(TEXT("Material'/Game/Weapons/skateboard/1/Trucks.Trucks'"));
	
	
	SkateboardMesh->SetMaterial(0, SkateboardBearing1Material.Object);
	SkateboardMesh->SetMaterial(1, SkateboardBearing2Material.Object);
	SkateboardMesh->SetMaterial(2, SkateboardWheelMaterial.Object);
	SkateboardMesh->SetMaterial(3, SkateboardBoltsMaterial.Object);
	SkateboardMesh->SetMaterial(4, SkateboardGripMaterial.Object);
	SkateboardMesh->SetMaterial(5, SkateboardDeckBottomMaterial.Object);
	SkateboardMesh->SetMaterial(6, SkateboardSideMaterial.Object);
	SkateboardMesh->SetMaterial(7, SkateboardTrucksMaterial.Object);

	if (SkateboardMeshAsset.Object)
	{
		SkateboardMesh->SetStaticMesh(SkateboardMeshAsset.Object);
	}

	SkateboardMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkateboardMesh->SetMobility(EComponentMobility::Movable);
	SkateboardMesh->SetWorldLocationAndRotation(FVector(0, -3, 0), FRotator(45, 0, 90));

}

// Called when the game starts or when spawned
void ASkateboard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkateboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* ASkateboard::GetMesh()
{
	return SkateboardMesh;
}

void ASkateboard::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Attack pressed"));
	if (FirstAttackMontage) 
		UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->PlayAnimMontage(FirstAttackMontage, 1, NAME_None);
}
void ASkateboard::AerialAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Aerial Attack pressed"));
}
void ASkateboard::ModeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Attack pressed"));
}
void ASkateboard::ModeAerialAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Aerial Attack pressed"));
}
void ASkateboard::ForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Forward Attack pressed"));
}
void ASkateboard::BackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Backward Attack pressed"));
}
void ASkateboard::LeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Leftward Attack pressed"));
}
void ASkateboard::RightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Rightward Attack pressed"));
}
void ASkateboard::AerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Aerial Forward Attack pressed"));
}
void ASkateboard::AerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Aerial Backward Attack pressed"));
}
void ASkateboard::AerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Aerial Leftward Attack pressed"));
}
void ASkateboard::AerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Aerial Rightward Attack pressed"));
}
void ASkateboard::ModeForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Forward Attack pressed"));
}
void ASkateboard::ModeBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Backward Attack pressed"));
}
void ASkateboard::ModeLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Leftward Attack pressed"));
}
void ASkateboard::ModeRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Rightward Attack pressed"));
}
void ASkateboard::ModeAerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Aerial Forward Attack pressed"));
}
void ASkateboard::ModeAerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Aerial Backward Attack pressed"));
}
void ASkateboard::ModeAerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Aerial Leftward Attack pressed"));
}
void ASkateboard::ModeAerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Mode Aerial Rightward Attack pressed"));
}

