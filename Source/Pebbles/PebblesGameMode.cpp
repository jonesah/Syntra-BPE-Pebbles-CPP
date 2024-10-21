// Copyright Epic Games, Inc. All Rights Reserved.

#include "PebblesGameMode.h"
#include "PebblesCharacter.h"
#include "UObject/ConstructorHelpers.h"

APebblesGameMode::APebblesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
