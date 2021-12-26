// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "EngineUtils.h"

#include "FPSCharacter.h"

////////////////////////////
/// GameState is a companion class of GameMode, it`s spawned by GameMode and works ONLY on Clients
/// Its a "container" for every thing we want to replicate from GameMode


void AFPSGameState::MultiCastOnCompleteMission_Implementation(APawn* InstigatroPawn, bool bMissionSuccess)	// Executes separatly on every Client
{
	UE_LOG(LogTemp, Warning, TEXT("MultiCast is running!"));
	for(TActorIterator<AFPSCharacter> Player(GetWorld()); Player; ++Player)	// Iterating through all Pawn in the level INCLUDING AIGuards
	{
		if(Player)		// This will be True only when passing Player Pawn
		{
			Player->DisableInput(nullptr);
			UE_LOG(LogTemp, Warning, TEXT("Disableing Input!"));
		}
	}
}
