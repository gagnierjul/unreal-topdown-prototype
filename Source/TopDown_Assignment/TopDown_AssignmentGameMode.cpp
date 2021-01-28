// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDown_AssignmentGameMode.h"
#include "TopDown_AssignmentPlayerController.h"
#include "TopDown_AssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDown_AssignmentGameMode::ATopDown_AssignmentGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDown_AssignmentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}