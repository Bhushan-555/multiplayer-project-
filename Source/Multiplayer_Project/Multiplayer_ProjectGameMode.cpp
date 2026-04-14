// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multiplayer_ProjectGameMode.h"
#include "Multiplayer_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayer_ProjectGameMode::AMultiplayer_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
