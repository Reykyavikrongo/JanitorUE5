// Fill out your copyright notice in the Description page of Project Settings.


#include "Skateboard.h"

// Sets default values
ASkateboard::ASkateboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
void ASkateboard::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Skateboard) Attack pressed"));
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

