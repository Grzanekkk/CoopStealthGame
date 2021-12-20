// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"

#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
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
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 12, FColor::Red, false, 10.f);
	}

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if(GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
	
}

void AAIGuard::OnNoiceHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Orange, false, 10.f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrinatation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrinatation, this, &AAIGuard::ResetOrinetation, 3.0f);
}

void AAIGuard::ResetOrinetation()
{
	SetActorRotation(OriginalRotation);
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
	
	SensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	SensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiceHeard);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}