// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// ModeState will dictate which move is used based on the current state

UENUM(BlueprintType)
enum class ModeState : uint8 {
	Ranged,
	Melee
};

UENUM(BlueprintType)
enum class TauntState : uint8 {
	Taunt,
	NotTaunt
};

UENUM(BlueprintType)
enum class DirectionENUM : uint8 {
	NoDirection,
	Front,
	Back,
	Left,
	Right
};

// determines the priority of actions that will take place, used for animation cancels and whatnot
UENUM(BlueprintType)
enum class AnimationTier : uint8 {
	// Tiers are ordered based on their priority, in this case Idle is smallest in terms of priority and cancelable (if there will ever be anything that is uncancelable) is the most important.
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA(DisplayName = "Moving"),
	Taunting UMETA(DisplayName = "Taunting"),
	Dodging UMETA(DisplayName = "Dodging"),
	Attacking UMETA(DisplayName = "Attacking"),
	JumpCancel UMETA(DisplayName = "JumpCancel"),
	Hit UMETA(DisplayName = "Hit"),
	OmniCancel UMETA(DisplayName = "OmniCancel"),
	Uncancelable UMETA(DisplayName = "Uncancelable")
};

/* this section is for 
ALL typedef declarations*/
// Function pointer that points to the function of the attack that will happen once the char stops being busy with another animation
using BufferedAttack = void(*)(DirectionENUM Direction);

/**
 * 
 */
class JANITORUE5_API ENUMS
{
public:
	ENUMS();
	~ENUMS();
};
