// Copyright Epic Games, Inc. All Rights Reserved.

#include "JanitorCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


//TODO: figure out how to make the animation priority, also figure out when and where stuff should be called

//////////////////////////////////////////////////////////////////////////
// AJanitorCharacter

AJanitorCharacter::AJanitorCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 88.0f);

	// Deprecated, now implemented through the blueprints

	//Find Animation to set
	//static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationSalsa(TEXT("AnimSequence'/Game/Characters/Mannequin_UE4/Animations/Salsa_Dancing_Retargeted.Salsa_Dancing_Retargeted'"));
	//AnimSequence = AnimationSalsa.Object;

	//Find Montage To set
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageSalsa(TEXT("AnimMontage'/Game/Characters/Mannequin_UE4/Animations/SalsaMontage.SalsaMontage'"));
	TauntMontage = MontageSalsa.Object;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Lock On
	LockOnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Lock On"));
	LockOnSphere->SetupAttachment(RootComponent);
	LockOnSphere->SetSphereRadius(1000.0f);
	LockOnSphere->OnComponentBeginOverlap.AddDynamic(this, &AJanitorCharacter::OnBeginOverlapSphere);
	LockOnSphere->OnComponentEndOverlap.AddDynamic(this, &AJanitorCharacter::OnEndOverlapSphere);

	//FollowArrow
	FollowArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Follow Arrow"));
	FollowArrow->SetupAttachment(RootComponent);
	FollowArrow->AddLocalOffset(FVector(50, 0, 0));

	//LockOn arrow
	LockOnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LockOn Arrow"));
	LockOnArrow->SetupAttachment(RootComponent);
	LockOnArrow->SetHiddenInGame(true);
	LockOnArrow->AddLocalOffset(FVector(50, 0, 0));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.45f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(LockOnSphere);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a camera boom for when player locks on to enemy
	LockOnCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("LockOnCameraBoom"));
	LockOnCameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	LockOnCameraBoom->SetHiddenInGame(true);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a Lock on camera
	LockOnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LockOnCamera"));
	LockOnCamera->SetupAttachment(LockOnCameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	LockOnCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	LockOnCamera->SetHiddenInGame(false);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	JumpMaxCount = 2;

}

//////////////////////////////////////////////////////////////////////////
// Input

void AJanitorCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Initialize all weapons
	FActorSpawnParameters SpawnInfo;
	marbles = GetWorld()->SpawnActor<AMarbles>(AMarbles::StaticClass(), FTransform(), SpawnInfo);
	//marbles = NewObject<AMarbles>();
	CurrentRangedWeapon = marbles;
	broom = GetWorld()->SpawnActor<ABroom>(ABroom::StaticClass(), FTransform(), SpawnInfo);
	CurrentMeleeWeapon = broom;
	skate = GetWorld()->SpawnActor<ASkateboard>(ASkateboard::StaticClass(), FTransform(), SpawnInfo);
	watergun = GetWorld()->SpawnActor<AWatergun>(AWatergun::StaticClass(), FTransform(), SpawnInfo);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJanitorCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AJanitorCharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AJanitorCharacter::Attack);
	PlayerInputComponent->BindAction("RangedAttack", IE_Pressed, this, &AJanitorCharacter::RangedAttack);
	PlayerInputComponent->BindAction("ModeAttack", IE_Pressed, this, &AJanitorCharacter::ModeAttack);
	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AJanitorCharacter::LockOn);
	PlayerInputComponent->BindAction("LockOn", IE_Released, this, &AJanitorCharacter::UnLockOn);
	PlayerInputComponent->BindAction("SwapLockOn", IE_Pressed, this, &AJanitorCharacter::SwapLockOn);
	PlayerInputComponent->BindAction("AKey", IE_Pressed, this, &AJanitorCharacter::APressed);
	PlayerInputComponent->BindAction("AKey", IE_Released, this, &AJanitorCharacter::AUnPressed);
	PlayerInputComponent->BindAction("SKey", IE_Pressed, this, &AJanitorCharacter::SPressed);
	PlayerInputComponent->BindAction("SKey", IE_Released, this, &AJanitorCharacter::SUnPressed);
	PlayerInputComponent->BindAction("DKey", IE_Pressed, this, &AJanitorCharacter::DPressed);
	PlayerInputComponent->BindAction("DKey", IE_Released, this, &AJanitorCharacter::DUnPressed);
	PlayerInputComponent->BindAction("WKey", IE_Pressed, this, &AJanitorCharacter::WPressed);
	PlayerInputComponent->BindAction("WKey", IE_Released, this, &AJanitorCharacter::WUnPressed);
	PlayerInputComponent->BindAction("ChangeStyle", IE_Pressed, this, &AJanitorCharacter::ChangeStyle);
	PlayerInputComponent->BindAction("SelectBroom", IE_Pressed, this, &AJanitorCharacter::SwapBroom);
	PlayerInputComponent->BindAction("SelectMarbles", IE_Pressed, this, &AJanitorCharacter::SwapMarbles);
	PlayerInputComponent->BindAction("SelectSkateboard", IE_Pressed, this, &AJanitorCharacter::SwapSkateboard);
	PlayerInputComponent->BindAction("SelectWatergun", IE_Pressed, this, &AJanitorCharacter::SwapWatergun);
	PlayerInputComponent->BindAction("ToggleTauntMode", IE_Pressed, this, &AJanitorCharacter::ToggleTaunt);
	PlayerInputComponent->BindAction("TauntAction", IE_Pressed, this, &AJanitorCharacter::TauntAction);


	PlayerInputComponent->BindAxis("MoveForward", this, &AJanitorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJanitorCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJanitorCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJanitorCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJanitorCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJanitorCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AJanitorCharacter::OnResetVR);
}


void AJanitorCharacter::OnResetVR()
{
	// If Janitor is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Janitor.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJanitorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//check if the characer has belocity and set is moving to true if velocity is above 0
	FVector xyz = this->GetVelocity();
	float x = xyz.X;
	float y = xyz.Y;
	float z = xyz.Z;
	if (x != 0.0f || y != 0.0f || z != 0.0f)
	{
		if (!IsMoving)
			StartMoving();
	}
	else
	{
		if (IsMoving)
			StopMoving();
	}
	
	// ismovingonground checks if the character is touching the floor, is moving if it's moving
	if (this->GetCharacterMovement()->IsMovingOnGround() && IsMoving && MovementIsBeingInput)
	{
		if (CurrentAnimTier != AnimationTier::Walking)
			CurrentAnimTier = AnimationTier::Walking;
	}

	if (WKeyPressed || SKeyPressed || AKeyPressed || DKeyPressed || JumpPressed)
	{
		MovementIsBeingInput = true;
		if (CurrentAnimTier == AnimationTier::Taunting)
		{
			CancelCheck(AnimationTier::Taunting);
		}
	}
	else
	{
		MovementIsBeingInput = false;
	}

	if (CurrentRangedWeapon == marbles)
	{
		if (IsLockedOn)
			marbles->ProjectileTransform = LockOnArrow->GetComponentTransform();
		else
			marbles->ProjectileTransform = FollowArrow->GetComponentTransform();
	}
		

	if (IsLockedOn)
	{
		if (LockOnablePawnArray.IsValidIndex(LockOnIndex))
		{
			this->SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->K2_GetActorLocation(), LockOnablePawnArray[LockOnIndex]->GetActorLocation()).Yaw, 0));
			float distanceX, distanceY, distanceZ;
			FVector EnemyLocation = LockOnablePawnArray[LockOnIndex]->GetActorLocation();
			FVector PlayerLocation = this->K2_GetActorLocation();
			FVector Mid = FVector((EnemyLocation.X + PlayerLocation.X) / 2, (EnemyLocation.Y + PlayerLocation.Y) / 2, (EnemyLocation.Z + PlayerLocation.Z) / 2);
			if (Mid.X >= PlayerLocation.X)
				distanceX = Mid.X - PlayerLocation.X;
			else
				distanceX = PlayerLocation.X - Mid.X;
			if (Mid.Y >= PlayerLocation.Y)
				distanceY = Mid.Y - PlayerLocation.Y;
			else
				distanceY = PlayerLocation.Y - Mid.Y;
			if (Mid.Z >= PlayerLocation.Z)
				distanceZ = Mid.Z - PlayerLocation.Z;
			else
				distanceZ = PlayerLocation.Z - Mid.Z;
			LockOnCameraBoom->TargetArmLength = 600.0f + sqrt(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);
			LockOnCameraBoom->SetWorldLocation(Mid);
			FollowCamera->SetActive(false);
			LockOnCamera->SetActive(true);
		}
		else
		{
			if (LockOnIndex == 0)
			{
				LockOnCamera->SetActive(false);
				FollowCamera->SetActive(true);
			}
			else
				LockOnIndex = 0;
		}
	}
}

void AJanitorCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (JumpCounter >= JumpMaxCount)
	{
		return;
	}
	Jump();
}

void AJanitorCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AJanitorCharacter::Landed(const FHitResult& HR)
{
	Super::Landed(HR);
	IsAirborne = false;
	JumpCounter = 0;
}

void AJanitorCharacter::Jump()
{
	// depending on taunt mode character will either be able to double jump (not taunt mode) or teleport upwards (taunt mode)
	if (TauntModeState == TauntState::Taunt)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("jump taunt mode"));
	}
	else
	{
		JumpPressed = true;
		if (IsAirborne && (JumpCounter < JumpMaxCount))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("airjump"));
			JumpCounter++;
			DoubleJump();
		}
		else if (JumpCounter < JumpMaxCount) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("ground jump"));
			IsAirborne = true;
			Super::Jump();
			JumpCounter++;
		}
	}
}

void AJanitorCharacter::StopJumping()
{

	JumpPressed = false;
	Super::StopJumping();
}

void AJanitorCharacter::DoubleJump()
{
	GetCharacterMovement()->DoJump(false);
}


void AJanitorCharacter::TauntAction()
{

	StartTaunting();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Taunt Action"));
	if (TauntMontage) 
	{
		PlayAnimMontage(TauntMontage, 1,NAME_None);
	}
	

	//USkeletalMeshComponent* MeshComponent = this->FindComponentByClass<USkeletalMeshComponent>();
	//if (MeshComponent)
	//{
	//	UAnimInstance* AnimInst = MeshComponent->GetAnimInstance();
	//	if (AnimInst)
	//	{
	//		MeshComponent->PlayAnimation(AnimSequence, false);
	//		float animLen = MeshComponent->GetSingleNodeInstance()->GetLength();
	//		animLen -= 0.34f;
	//		GetWorldTimerManager().SetTimer(PostAnimTimerHandle, this, &AJanitorCharacter::PostAnimFunc, animLen, false);
	//	}
	//}
	//return;
}

void AJanitorCharacter::PostAnimFunc() 
{

}

void AJanitorCharacter::Cancel()
{
	this->StopAnimMontage(this->GetCurrentMontage());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Cancel function called"));
	//called in blueprints to change animations that are currently running
}

//returns if the called action takes precedent over the current action
bool AJanitorCharacter::CancelCheck(AnimationTier AT)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("cancelcheck function called"));
	if (CurrentAnimTier == AnimationTier::Taunting && AT == AnimationTier::Walking)
	{
		Cancel();
		return true;
	}
	if (AT < CurrentAnimTier)
	{
		return false;
	}
	else {
		Cancel();
		return true;
	}
}

void GotHit()
{

}

void AJanitorCharacter::Attack()
{
	StartAttacking();
	if (TauntModeState == TauntState::Taunt)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Attack taunt mode"));
	}
	else
	{
		if (!IsLockedOn)
		{
			if (!IsAirborne)
				CurrentMeleeWeapon->Attack();
			else CurrentMeleeWeapon->AerialAttack();
		}
		else
		{
			FString Direction = GetDirection();
			if (Direction == "front")
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->ForwardAttack();
				else CurrentMeleeWeapon->AerialForwardAttack();
			}
			else if (Direction == "back")
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->BackwardAttack();
				else CurrentMeleeWeapon->AerialBackwardAttack();
			}
			else if (Direction == "left")
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->LeftwardAttack();
				else CurrentMeleeWeapon->AerialLeftwardAttack();
			}
			else if (Direction == "right")
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->RightwardAttack();
				else CurrentMeleeWeapon->AerialRightwardAttack();
			}
			else
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->Attack();
				else CurrentMeleeWeapon->AerialAttack();
			}
		}
	}
	StopAttacking();
}

void AJanitorCharacter::RangedAttack()
{
	StartAttacking();
	if (TauntModeState == TauntState::Taunt)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Ranged Attack Taunt mode"));
	}
	else
	{
		if (!IsLockedOn)
		{
			if (!IsAirborne)
				CurrentRangedWeapon->Attack();
			else CurrentRangedWeapon->AerialAttack();
		}
		else
		{
			FString Direction = GetDirection();
			if (Direction == "front")
			{
				if (!IsAirborne)
					CurrentRangedWeapon->ForwardAttack();
				else CurrentRangedWeapon->AerialForwardAttack();
			}
			else if (Direction == "back")
			{
				if (!IsAirborne)
					CurrentRangedWeapon->BackwardAttack();
				else CurrentRangedWeapon->AerialBackwardAttack();
			}
			else if (Direction == "left")
			{
				if (!IsAirborne)
					CurrentRangedWeapon->LeftwardAttack();
				else CurrentRangedWeapon->AerialLeftwardAttack();

			}
			else if (Direction == "right")
			{
				if (!IsAirborne)
					CurrentRangedWeapon->RightwardAttack();
				else CurrentRangedWeapon->AerialRightwardAttack();
			}
			else
			{
				if (!IsAirborne)
					CurrentRangedWeapon->Attack();
				else CurrentRangedWeapon->AerialAttack();
			}
		}
	}
	StopAttacking();
}

void AJanitorCharacter::ModeAttack()
{
	StartAttacking();
	if (TauntModeState == TauntState::Taunt)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Mode Attack Taunt Mode"));
	}
	else
	{
		if (!IsLockedOn)
		{
			if (AttackModeState == ModeState::Ranged)
			{
				if (!IsAirborne)
					CurrentRangedWeapon->ModeAttack();
				else CurrentRangedWeapon->ModeAerialAttack();
			}
			else
			{
				if (!IsAirborne)
					CurrentMeleeWeapon->ModeAttack();
				else CurrentMeleeWeapon->ModeAerialAttack();
			}
		}
		else
		{
			FString Direction = GetDirection();
			if (Direction == "front")
			{
				if (AttackModeState == ModeState::Ranged)
				{
					if (!IsAirborne)
						CurrentRangedWeapon->ModeForwardAttack();
					else CurrentRangedWeapon->ModeAerialForwardAttack();
				}
				else
				{
					if (!IsAirborne)
						CurrentMeleeWeapon->ModeForwardAttack();
					else CurrentMeleeWeapon->ModeAerialForwardAttack();
				}
			}
			else if (Direction == "back")
			{
				if (AttackModeState == ModeState::Ranged)
				{
					if (!IsAirborne)
						CurrentRangedWeapon->ModeBackwardAttack();
					else CurrentRangedWeapon->ModeAerialBackwardAttack();
				}
				else
				{
					if (!IsAirborne)
						CurrentMeleeWeapon->ModeBackwardAttack();
					else CurrentMeleeWeapon->ModeAerialBackwardAttack();
				}
			}
			else if (Direction == "left")
			{
				if (AttackModeState == ModeState::Ranged)
				{
					if (!IsAirborne)
						CurrentRangedWeapon->ModeLeftwardAttack();
					else CurrentRangedWeapon->ModeAerialLeftwardAttack();
				}
				else
				{
					if (!IsAirborne)
						CurrentMeleeWeapon->ModeLeftwardAttack();
					else CurrentMeleeWeapon->ModeAerialLeftwardAttack();
				}
			}
			else if (Direction == "right")
			{
				if (AttackModeState == ModeState::Ranged)
				{
					if (!IsAirborne)
						CurrentRangedWeapon->ModeRightwardAttack();
					else CurrentRangedWeapon->ModeAerialRightwardAttack();
				}
				else
				{
					if (!IsAirborne)
						CurrentMeleeWeapon->ModeRightwardAttack();
					else CurrentMeleeWeapon->ModeAerialRightwardAttack();
				}
			}
			else
			{
				if (AttackModeState == ModeState::Ranged)
				{
					if (!IsAirborne)
						CurrentRangedWeapon->ModeAttack();
					else CurrentRangedWeapon->ModeAerialAttack();
				}
				else
				{
					if (!IsAirborne)
						CurrentMeleeWeapon->ModeAttack();
					else CurrentMeleeWeapon->ModeAerialAttack();
				}
			}
		}
	}
	StopAttacking();
}


void AJanitorCharacter::StartAttacking()
{
	CancelCheck(AnimationTier::Attacking);
	CurrentAnimTier = AnimationTier::Attacking;

}

void AJanitorCharacter::StopAttacking()
{
}

void AJanitorCharacter::StartDodging()
{
	CancelCheck(AnimationTier::Dodging);
	CurrentAnimTier = AnimationTier::Dodging;

}

void AJanitorCharacter::StopDodging()
{
}

void AJanitorCharacter::StartTaunting()
{
	CancelCheck(AnimationTier::Taunting);
	CurrentAnimTier = AnimationTier::Taunting;
}

void AJanitorCharacter::StopTaunting()
{
}

void AJanitorCharacter::StartMoving()
{
	IsMoving = true;
}

void AJanitorCharacter::StopMoving()
{
	IsMoving = false;
}

void AJanitorCharacter::StartInvulnerable() 
{
	IsInvulnerable = true;
}

void AJanitorCharacter::StopInvulnerable()
{
	IsInvulnerable = false;
}

FString AJanitorCharacter::GetDirection()
{
	// Gets the precise angle between the player and the enemy to determine the directional input that needs to be held to do certain attacks/actions
	FRotator ArrowRotation;

	float ArrowRotationYaw;
	if (LockOnablePawnArray.IsValidIndex(LockOnIndex))
	{
		ArrowRotation = UKismetMathLibrary::FindLookAtRotation(this->K2_GetActorLocation(), LockOnablePawnArray[LockOnIndex]->GetActorLocation());
		ArrowRotationYaw = ArrowRotation.Yaw;
	}
	else
	{
		ArrowRotation = FollowArrow->K2_GetComponentRotation();
		ArrowRotationYaw = ArrowRotation.Yaw;
	}

	LockOnArrow->SetWorldRotation(FRotator(0, ArrowRotation.Yaw, 0));
	float LockOnCameraRotationYaw = LockOnCamera->K2_GetComponentRotation().Yaw;
	if (ArrowRotationYaw <= 0)
		ArrowRotationYaw *= -1;
	else
	{
		ArrowRotationYaw *= -1;
		ArrowRotationYaw += 360;
	}
	if (LockOnCameraRotationYaw <= 0)
		LockOnCameraRotationYaw *= -1;
	else
	{
		LockOnCameraRotationYaw *= -1;
		LockOnCameraRotationYaw += 360;
	}
	float Yaw;

	Yaw = ArrowRotationYaw - LockOnCameraRotationYaw;
	if (Yaw < 0)
		Yaw += 360;

	if ((Yaw >= 315 && Yaw <= 360) || (Yaw <= 45 && Yaw >= 0))
	{
		if (WKeyPressed)
			return "front";
		else if (SKeyPressed)
			return "back";
		else if (AKeyPressed)
			return "left";
		else if (DKeyPressed)
			return "right";
	}
	else if (Yaw > 45 && Yaw <= 135)
	{
		if (WKeyPressed)
			return "right";
		else if (SKeyPressed)
			return "left";
		else if (AKeyPressed)
			return "front";
		else if (DKeyPressed)
			return "back";
	}
	else if (Yaw > 135 && Yaw <= 225)
	{
		if (WKeyPressed)
			return "back";
		else if (SKeyPressed)
			return "front";
		else if (AKeyPressed)
			return "left";
		else if (DKeyPressed)
			return "right";
	}
	else
	{
		if (WKeyPressed)
			return "left";
		else if (SKeyPressed)
			return "right";
		else if (AKeyPressed)
			return "back";
		else if (DKeyPressed)
			return "front";
	}
	return "0";
}

void AJanitorCharacter::LockOn()
{
	LockOnIndex = 0;
	IsLockedOn = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AJanitorCharacter::UnLockOn()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	IsLockedOn = false;
	LockOnCamera->SetActive(false);
	FollowCamera->SetActive(true);
}

void AJanitorCharacter::SwapLockOn()
{
	++LockOnIndex;
	if (!LockOnablePawnArray.IsValidIndex(LockOnIndex))
		LockOnIndex = 0;
}

void AJanitorCharacter::ToggleTaunt()
{
	if (TauntModeState == TauntState::NotTaunt)
	{
		TauntModeState = TauntState::Taunt;
	}
	else
	{
		TauntModeState = TauntState::NotTaunt;
	}
}

void AJanitorCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJanitorCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJanitorCharacter::MoveForward(float Value)
{
	StartMoving();
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJanitorCharacter::ChangeStyle()
{
	if (AttackModeState == ModeState::Ranged)
	{
		AttackModeState = ModeState::Melee;
	}
	else
	{
		AttackModeState = ModeState::Ranged;
	}
}

void AJanitorCharacter::MoveRight(float Value)
{
	StartMoving();
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AJanitorCharacter::OnBeginOverlapSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ALockOnablePawn::StaticClass()) || OtherActor->IsA(ABasicEnemy::StaticClass()))
	{
		++LockOnQuantity;
		ALockOnablePawn* temp = Cast<ALockOnablePawn>(OtherActor);
		temp->LockOnComponent->SetText(FText::FromString(FString::FromInt(LockOnQuantity)));
		LockOnablePawnArray.Add(temp);
	}
}

void AJanitorCharacter::OnEndOverlapSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ALockOnablePawn::StaticClass()) || OtherActor->IsA(ABasicEnemy::StaticClass()))
	{
		--LockOnQuantity;
		ALockOnablePawn* temp = Cast<ALockOnablePawn>(OtherActor);
		temp->LockOnComponent->SetText(FText::FromString(""));
		int index = LockOnablePawnArray.Find(temp);
		LockOnablePawnArray.Remove(temp);
		for (int i = 0; i < LockOnablePawnArray.Num(); ++i)
		{
			LockOnablePawnArray[i]->LockOnComponent->SetText(FText::FromString(FString::FromInt(i + 1)));
		}
	}
}

void AJanitorCharacter::SwapWatergun()
{
	if (CurrentRangedWeapon == watergun)
	{

	}
	else {
	CurrentRangedWeapon = watergun;
	}
}
void AJanitorCharacter::SwapBroom()
{
	if (CurrentMeleeWeapon == broom)
	{

	}
	else {
		CurrentMeleeWeapon = broom;
	}
	
}
void AJanitorCharacter::SwapMarbles()
{
	if (CurrentRangedWeapon == marbles)
	{

	}
	else {
		CurrentRangedWeapon = marbles;
	}
}

void AJanitorCharacter::SwapSkateboard()
{
	if (CurrentMeleeWeapon == skate)
	{

	}
	else {
		CurrentMeleeWeapon = skate;
	}
}


void AJanitorCharacter::WPressed()
{
	WKeyPressed = true;
}

void AJanitorCharacter::WUnPressed()
{
	WKeyPressed = false;
}

void AJanitorCharacter::SPressed()
{
	SKeyPressed = true;
}

void AJanitorCharacter::SUnPressed()
{
	SKeyPressed = false;
}

void AJanitorCharacter::APressed()
{
	AKeyPressed = true;
}

void AJanitorCharacter::AUnPressed()
{
	AKeyPressed = false;
}

void AJanitorCharacter::DPressed()
{
	DKeyPressed = true;
}

void AJanitorCharacter::DUnPressed()
{
	DKeyPressed = false;
}

