// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"

#include "DrawDebugHelpers.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if(SeenPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Seen!!!"));
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 12, FColor::Orange, false, 10.f);
	}
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();

	SensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}