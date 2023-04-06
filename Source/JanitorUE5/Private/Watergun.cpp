// Fill out your copyright notice in the Description page of Project Settings.


#include "Watergun.h"

// Sets default values
AWatergun::AWatergun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWatergun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWatergun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWatergun::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Attack pressed"));
}
void AWatergun::AerialAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Aerial Attack pressed"));
}
void AWatergun::ModeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Attack pressed"));
}
void AWatergun::ModeAerialAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Aerial Attack pressed"));
}
void AWatergun::ForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Forward Attack pressed"));
}
void AWatergun::BackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Backward Attack pressed"));
}
void AWatergun::LeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Leftward Attack pressed"));
}
void AWatergun::RightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Rightward Attack pressed"));
}
void AWatergun::AerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Aerial Forward Attack pressed"));
}
void AWatergun::AerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Aerial Backward Attack pressed"));
}
void AWatergun::AerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Aerial Leftward Attack pressed"));
}
void AWatergun::AerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Aerial Rightward Attack pressed"));
}
void AWatergun::ModeForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Forward Attack pressed"));
}
void AWatergun::ModeBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Backward Attack pressed"));
}
void AWatergun::ModeLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Leftward Attack pressed"));
}
void AWatergun::ModeRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Rightward Attack pressed"));
}
void AWatergun::ModeAerialForwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Aerial Forward Attack pressed"));
}
void AWatergun::ModeAerialBackwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Aerial Backward Attack pressed"));
}
void AWatergun::ModeAerialLeftwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Aerial Leftward Attack pressed"));
}
void AWatergun::ModeAerialRightwardAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Watergun) Mode Aerial Rightward Attack pressed"));
}
