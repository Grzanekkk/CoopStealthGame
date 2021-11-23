// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopStealthGameGameMode.h"
#include "CoopStealthGameHUD.h"
#include "CoopStealthGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoopStealthGameGameMode::ACoopStealthGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACoopStealthGameHUD::StaticClass();
}
