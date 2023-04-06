// Fill out your copyright notice in the Description page of Project Settings.


#include "Broom.h"

// Sets default values
ABroom::ABroom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABroom::Attack() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("(Broom) Attack pressed"));
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

