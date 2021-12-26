// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"

#include "FPSGameState.h"
#include "FPSHUD.h"
#include "FPSPlayerController.h"
#include "UObject/ConstructorHelpers.h"

/////////////////////
/// There is NO instance of GameMode on Clients, so NONE of this code will be run on Clients, it`s SERVER ONLYs
/// We also cant use MultiCast functions here, or replicate anything
/// And for this reason we have to use GameState


AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
	// PlayerControllerClass = AFPSPlayerController::StaticClass();		// We want to use BP version
}

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSGameMode::CompleteMission(APawn* InstigatroPawn, bool bMissionSuccess)
{
	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if(GS)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState Found!"));
		GS->MultiCastOnCompleteMission(InstigatroPawn, bMissionSuccess);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO GameState Found!"));
	}
}