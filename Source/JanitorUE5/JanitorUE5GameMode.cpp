// Copyright Epic Games, Inc. All Rights Reserved.

#include "JanitorUE5GameMode.h"
#include "JanitorUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AJanitorUE5GameMode::AJanitorUE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/JanitorCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
