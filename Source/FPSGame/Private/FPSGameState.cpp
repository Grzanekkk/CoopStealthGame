// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "EngineUtils.h"

#include "FPSCharacter.h"
#include "FPSPlayerController.h"

////////////////////////////
/// GameState is a companion class of GameMode, it`s spawned by GameMode and works ONLY on Clients
/// Its a "container" for every thing we want to replicate from GameMode


void AFPSGameState::MultiCastOnCompleteMission_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)	// Executes on every Client and on the server
{
	for (TPlayerControllerIterator<AFPSPlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		AFPSPlayerController* PC = *It;
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionComplete(InstigatorPawn, bMissionSuccess);
			APawn* Pawn = It->GetPawn();
			if (Pawn)
			{
				Pawn->DisableInput(nullptr);
				UE_LOG(LogTemp, Warning, TEXT("Disableing Input!"));
			}
		}
	}
}
