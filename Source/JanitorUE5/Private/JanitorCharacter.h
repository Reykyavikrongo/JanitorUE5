// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LockOnablePawn.h"
#include "WeaponClass.h"
#include "Marbles.h"
#include "Broom.h"
#include "Watergun.h"
#include "Skateboard.h"
#include "BasicEnemy.h"
#include "Blueprint/UserWidget.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "JanitorCharacter.generated.h"

// ModeState will dictate which move is used based on the current state
UENUM(BlueprintType)
enum class ModeState : uint8{
	Ranged,
	Melee
};

UENUM(BlueprintType)
enum class TauntState : uint8 {
	Taunt,
	NotTaunt
};

// determines the priority of actions that will take place, used for animation cancels and whatnot
UENUM(BlueprintType)
enum class AnimationTier : uint8 {
	// Tiers are ordered based on their priority, in this case Idle is smallest in terms of priority and uncancelable (if there will ever be anything that is uncancelable) is the most important.
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Taunting UMETA(DisplayName = "Taunting"),
	Dodging UMETA(DisplayName = "Dodging"),
	Attacking UMETA(DisplayName = "Attacking"),
	JumpCancel UMETA(DisplayName = "JumpCancel"),
	Hit UMETA(DisplayName = "Hit"),
	OmniCancel UMETA(DisplayName = "OmniCancel"),
	Uncancelable UMETA(DisplayName = "Uncancelable")
};

UCLASS()
class AJanitorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera boom positioning the camera between the currently locked on enemy and the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LockOnCamera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* LockOnCameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** LockOn camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LockOnCamera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* LockOnCamera;

	/** Player vision radius */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sensing, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* LockOnSphere;

	/** Arrow that will be turned towards the enemy once it is locked on, this will be used to dictate the direction projectiles will travel*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrow, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* LockOnArrow;

	/** Follow arrow that will always be facing the same way the player is facing, probably no use, might delete later if left useless*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrow, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FollowArrow;


	// Keeps track of how many enemies are inside the player vision sphere component
	int LockOnQuantity;
	// Keeps track of if the lock on key is being held
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LockOn, meta = (AllowPrivateAccess = "true"))
	bool IsLockedOn;
	// bool to keep track is the player moving or not
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	bool IsMoving = false;
	// bool to keep track is the player moving or not
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	bool MovementIsBeingInput = false;
	// Does the character have I frames
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	bool IsInvulnerable = false;
	// keeps track of if player is in the air, also used to determine which attack will be done
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	bool IsAirborne = false;
	// is jump being held at the moment
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	bool JumpPressed = false;

	
	 
	// Keeps track of which enemy is being locked on to currently
	int LockOnIndex;
	// Keeps track of which directional input is being held at the moment, used to determine which attack will be used
	bool WKeyPressed, AKeyPressed, SKeyPressed, DKeyPressed = false;

	int JumpMaxCount = 2;
	

	// Pointers to current renged and melee weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RangedWeapon, meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IWeaponClass> CurrentRangedWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MeleeWeapon, meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IWeaponClass> CurrentMeleeWeapon;

	// define the variables for each weapon
	AMarbles* marbles;
	ABroom* broom;
	ASkateboard* skate;
	AWatergun* watergun;

	// jump counter/ max number of jumps.
	int JumpCounter = 0;


	//timer
	FTimerManager PostAnimTimerHandle;

public:
	AJanitorCharacter();

	//Current tier of the animation, used to determine whether an animation is going to be overridden
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animations)
	AnimationTier CurrentAnimTier = AnimationTier::Idle;

	// Set the default state/style
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RangedWeapon)
	ModeState AttackModeState = ModeState::Ranged;

	// Set the defult taunt state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	TauntState TauntModeState = TauntState::NotTaunt;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Keeps track of all of the entities that are lock on-able and inside the players sphere of vision*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TArray<ALockOnablePawn*> LockOnablePawnArray;


	//Deprecated, now being implemented with the blueprint editor for convenience and ease (fuck C++ animating)
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	//UAnimSequence* AnimSequence;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* TauntMontage;


	//Used to get the current montage that is being used. Used to cancel animations and stuff
	UPROPERTY(VisibleAnywhere, BlueprintType, Category = Animations)
	UAnimMontage* CurrentMontage;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void PostAnimFunc();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	void Jump();
	void StopJumping();
	UFUNCTION(BlueprintCallable, Category = "Jump")
	void DoubleJump();

	//Used to change the bool values when character is attacking, Moving, taunting etc.
	void StartAttacking();
	void StopAttacking();
	void StartDodging();
	void StopDodging();
	void StartMoving();
	void StopMoving();
	void StartTaunting();
	void StopTaunting();
	void StartInvulnerable();
	void StopInvulnerable();

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when the player starts attacking. */
	void Attack();
	void RangedAttack();
	void ModeAttack();
	void ChangeStyle();

	void LockOn();
	void UnLockOn();
	void SwapLockOn();

	void APressed();
	void AUnPressed();

	void SPressed();
	void SUnPressed();

	void DPressed();
	void DUnPressed();

	void WPressed();
	void WUnPressed();

	void SwapMarbles();
	void SwapBroom();
	void SwapSkateboard();
	void SwapWatergun();

	void ToggleTaunt();
	UFUNCTION(BlueprintCallable, Category="Taunting")
	void TauntAction();

	//function used to cancel animations
	UFUNCTION(BlueprintCallable, Category = "Taunting")
	void Cancel();

	//function that checks if the action which has been pressed is able to override the action that the character is performing that instant, returns true if the action that is being taken can be done, false if not
	bool CancelCheck(AnimationTier AT);

	//Handle all the operations when character gets hit
	void GotHit();

	FString GetDirection();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void Landed(const FHitResult& HR) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlapSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlapSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};