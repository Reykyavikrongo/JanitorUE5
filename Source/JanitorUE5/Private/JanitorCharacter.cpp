// Copyright Epic Games, Inc. All Rights Reserved.

#include "JanitorCharacter.h"
//#include "HeadMountedDisplayFunctionLibrary.h"
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


// TODO: broom attack needs anim notify states for hitboxes and animation ending because second or third attack isnt inputted.
// TODO: figure out input buffering
// TODO: make stinger animation(keep it simple), implement the movement


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

	//DirectionArrow
	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction Arrow"));
	DirectionArrow->SetupAttachment(RootComponent);
	DirectionArrow->SetHiddenInGame(false);

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


}

//////////////////////////////////////////////////////////////////////////
// Input

void AJanitorCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Initialize all weapons
	FActorSpawnParameters SpawnInfo;
	const FTransform orientation_socket_right_hand = GetMesh()->GetSocketTransform("Right_Hand_Weapon_Socket", ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_left_hand = GetMesh()->GetSocketTransform("Left_Hand_Weapon_Socket", ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_left_belt = GetMesh()->GetSocketTransform("Pelvis_Belt_Socket_Left", ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_left_back = GetMesh()->GetSocketTransform("Clavicle_Left_Back_Socket", ERelativeTransformSpace::RTS_World);

	// Initialize marbles and attch them to the sockets

	marbles = GetWorld()->SpawnActor<AMarbles>(AMarbles::StaticClass(), orientation_socket_left_belt, SpawnInfo);
	
	CurrentRangedWeapon = marbles;
	marbles->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Pelvis_Belt_Socket_Left");

	// initialize broom
	broom = GetWorld()->SpawnActor<ABroom>(ABroom::StaticClass(), orientation_socket_right_hand, SpawnInfo);
	
	CurrentMeleeWeapon = broom;
	broom->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Right_Hand_Weapon_Socket");
	FVector Offset = broom->GetActorLocation() + FVector(10,0,0);

	// initialize skate
	skate = GetWorld()->SpawnActor<ASkateboard>(ASkateboard::StaticClass(), orientation_socket_left_back, SpawnInfo);
	
	skate->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Clavicle_Left_Back_Socket");
	skate->GetMesh()->SetHiddenInGame(true);

	// initialize watergun
	watergun = GetWorld()->SpawnActor<AWatergun>(AWatergun::StaticClass(), orientation_socket_left_hand, SpawnInfo);

	watergun->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "Left_Hand_Weapon_Socket");
	watergun->GetMesh()->SetHiddenInGame(true);

	//onAnimTierChanged.AddDynamic(this, &AJanitorCharacter::AnimTierChangeHandler);


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
	//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJanitorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsMovingCheck();
	IsMovementBeingInputCheck();
	
	// ismovingonground checks if the character is touching the floor, is moving if it's moving
	// TODO:this makes no sense, the anim tier will be walking even if the char is stuck doing an animation
	// TODO:figure out if this even needs to exist (spoiler prob not)
	if (this->GetCharacterMovement()->IsMovingOnGround() && IsMoving && MovementIsBeingInput)
	{
		if (CurrentAnimTier != AnimationTier::Moving)
			CurrentAnimTier = AnimationTier::Moving;
	}

	if (CurrentRangedWeapon == marbles)
	{
		// TODO: change this to not be in tick, only check before marble is thrown (perhaps move it to marble class itself)
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
	if (JumpCounter >= MaxNOfJumps)
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
		if (IsAirborne && (JumpCounter < MaxNOfJumps))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("airjump"));
			JumpCounter++;
			DoubleJump();
		}
		else if (JumpCounter < MaxNOfJumps) {
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
	//doesn't work
	//GetCharacterMovement()->DoJump(false);

	LaunchCharacter(FVector(0, 0, 600), false, true);
}


void AJanitorCharacter::TauntAction()
{
	
	StartTaunting();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Taunt Action"));
	if (TauntMontage) 
	{
		this->PlayAnimMontage(TauntMontage, 1,NAME_None);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Animation Length: %f"), this->GetCurrentMontage()->GetPlayLength()));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Animation Length: %f"), this->GetCurrentMontage()->GetPlayLength()));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Animation Length: %f"), this->GetCurrentMontage()->GetPlayLength()));
	}
	

	/*
	USkeletalMeshComponent* MeshComponent = this->FindComponentByClass<USkeletalMeshComponent>();
	if (MeshComponent)
	{
		UAnimInstance* AnimInst = MeshComponent->GetAnimInstance();
		if (AnimInst)
		{
			MeshComponent->PlayAnimation(AnimSequence, false);
			float animLen = MeshComponent->GetSingleNodeInstance()->GetLength();
			animLen -= 0.34f;
			GetWorldTimerManager().SetTimer(PostAnimTimerHandle, this, &AJanitorCharacter::PostAnimFunc, animLen, false);
		}
	}
	return;*/
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
	if (CurrentAnimTier == AnimationTier::Taunting && AT == AnimationTier::Moving)
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
		if (CurrentAnimTier < AnimationTier::Attacking)
		{
			CurrentMeleeWeapon->DoAttack(GetDirection());
		}
		else
		{
			bufferedDirection = GetDirection();
			bufferedAttack = CurrentMeleeWeapon->DoAttack(bufferedDirection);
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
		StartAttacking();
		if (TauntModeState == TauntState::Taunt)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Attack taunt mode"));
		}
		else
		{
			if (CurrentAnimTier < AnimationTier::Attacking)
			{
				CurrentRangedWeapon->DoAttack(GetDirection());
			}
			else
			{
				bufferedDirection = GetDirection();
				bufferedAttack = CurrentRangedWeapon->DoAttack(bufferedDirection);
			}
		}
		StopAttacking();
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
		if (AttackModeState == ModeState::Melee)
		{
			if (CurrentAnimTier < AnimationTier::Attacking)
			{
				CurrentMeleeWeapon->DoModeAttack(GetDirection());
			}
			else
			{
				bufferedDirection = GetDirection();
				bufferedAttack = CurrentMeleeWeapon->DoModeAttack(bufferedDirection);
			}
		}
		else
		{
			if (CurrentAnimTier < AnimationTier::Attacking)
			{
				CurrentRangedWeapon->DoModeAttack(GetDirection());
			}
			else
			{
				bufferedDirection = GetDirection();
				bufferedAttack = CurrentRangedWeapon->DoModeAttack(bufferedDirection);
			}
		}
	}
	StopAttacking();
}

void AJanitorCharacter::DoBufferedAttack()
{
	if (bufferedAttack && CurrentAnimTier < AnimationTier::Attacking)
		bufferedAttack(bufferedDirection);
}

void AJanitorCharacter::AnimTierChangeHandler()
{
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

void AJanitorCharacter::IsMovingCheck()
{
	//check if the characer has belocity and set is moving to true if velocity is above 0
	if (!this->GetVelocity().IsZero())
	{
		if (!IsMoving)
			IsMoving = true;
	}
	else
	{
		if (IsMoving)
			IsMoving = false;
	}
}

void AJanitorCharacter::IsMovementBeingInputCheck()
{
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
}

void AJanitorCharacter::StartInvulnerable() 
{
	IsInvulnerable = true;
}

void AJanitorCharacter::StopInvulnerable()
{
	IsInvulnerable = false;
}

DirectionENUM AJanitorCharacter::GetDirection()
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
			return DirectionENUM::Front;
		else if (SKeyPressed)
			return DirectionENUM::Back;
		else if (AKeyPressed)
			return DirectionENUM::Left;
		else if (DKeyPressed)
			return DirectionENUM::Right;
	}
	else if (Yaw > 45 && Yaw <= 135)
	{
		if (WKeyPressed)
			return DirectionENUM::Right;
		else if (SKeyPressed)
			return DirectionENUM::Left;
		else if (AKeyPressed)
			return DirectionENUM::Front;
		else if (DKeyPressed)
			return DirectionENUM::Back;
	}
	else if (Yaw > 135 && Yaw <= 225)
	{
		if (WKeyPressed)
			return DirectionENUM::Back;
		else if (SKeyPressed)
			return DirectionENUM::Front;
		else if (AKeyPressed)
			return DirectionENUM::Left;
		else if (DKeyPressed)
			return DirectionENUM::Right;
	}
	else
	{
		if (WKeyPressed)
			return DirectionENUM::Left;
		else if (SKeyPressed)
			return DirectionENUM::Right;
		else if (AKeyPressed)
			return DirectionENUM::Back;
		else if (DKeyPressed)
			return DirectionENUM::Front;
	}
	return DirectionENUM::NoDirection;
}

void AJanitorCharacter::UpdateDirectionArrow(FVector Direction)
{
	// Direction arrow is used to see where the character is moving (or is going to move after an animation).

	DirectionArrow->SetWorldRotation(FRotator(0, Controller->GetControlRotation().Yaw, 0));

	int x = 0;
	int y = 0;
	int angle = 0;

	if (WKeyPressed)
		y += 1;
	if (SKeyPressed)
		y -= 1;
	if (AKeyPressed)
		x -= 1;
	if (DKeyPressed)
		x += 1;

	if (x != 0 && y != 0)
	{
		if (x == 1 && y == 1)
			angle = 45;
		else if (x == 1 && y == -1)
			angle = 135;
		else if (x == -1 && y == 1)
			angle = 315;
		else
			angle = 225;
	}
	else
	{
		if (x == 1)
			angle = 90;
		else if (x == -1)
			angle = 270;
		else if (y == 1)
			angle = 0;
		else
			angle = 180;
	}
	
	if (x == 0 && y == 0)
	{
		if (IsLockedOn)
			DirectionArrow->SetWorldRotation(LockOnArrow->GetRelativeRotation());
		else
			DirectionArrow->SetWorldRotation(FollowArrow->GetRelativeRotation());
	}
	DirectionArrow->AddWorldRotation(FRotator(0, angle, 0));
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

		UpdateDirectionArrow(Direction);
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

		UpdateDirectionArrow(Direction);
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

void AJanitorCharacter::WeaponBeingHeldChangeMelee()
{
	
}

void AJanitorCharacter::WeaponBeingHeldChangeRanged()
{

}

bool AJanitorCharacter::GetIsLockedOn()
{
	return IsLockedOn;
}

bool AJanitorCharacter::GetIsAirborne()
{
	return IsAirborne;
}

void AJanitorCharacter::SwapWatergun()
{
	if (CurrentRangedWeapon != watergun)
	{
		CurrentRangedWeapon->GetMesh()->SetHiddenInGame(true);
		CurrentRangedWeapon = watergun;
		CurrentRangedWeapon->GetMesh()->SetHiddenInGame(false);
	}
}
void AJanitorCharacter::SwapBroom()
{
	if (CurrentMeleeWeapon != broom)
	{
		CurrentMeleeWeapon->GetMesh()->SetHiddenInGame(true);
		CurrentMeleeWeapon = broom;
		CurrentMeleeWeapon->GetMesh()->SetHiddenInGame(false);
	}
}
void AJanitorCharacter::SwapMarbles()
{
	if (CurrentRangedWeapon != marbles)
	{
		CurrentRangedWeapon->GetMesh()->SetHiddenInGame(true);
		CurrentRangedWeapon = marbles;
		CurrentRangedWeapon->GetMesh()->SetHiddenInGame(false);
	}
}

void AJanitorCharacter::SwapSkateboard()
{
	if (CurrentMeleeWeapon != skate)
	{
		CurrentMeleeWeapon->GetMesh()->SetHiddenInGame(true);
		CurrentMeleeWeapon = skate;
		CurrentMeleeWeapon->GetMesh()->SetHiddenInGame(false);
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

