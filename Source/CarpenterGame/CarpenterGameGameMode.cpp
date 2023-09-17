// Copyright Epic Games, Inc. All Rights Reserved.

#include "CarpenterGameGameMode.h"
#include "CarpenterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACarpenterGameGameMode::ACarpenterGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
