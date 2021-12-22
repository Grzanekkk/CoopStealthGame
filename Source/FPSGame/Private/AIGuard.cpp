// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuard.h"

#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Perception/PawnSensingComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));

	GuardState = EAIState::Idle;
}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if(!SeenPawn)
		return
	
	SetGuardState(EAIState::Alerted);		// If Guard saw you you loose!
	
	UE_LOG(LogTemp, Warning, TEXT("Player Seen!!!"));
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 12, FColor::Red, false, 10.f);

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if(GM)
	{
		GM->CompleteMission(SeenPawn, false);		
	}

	StopMovement();
}

void AAIGuard::OnNoiceHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if(GuardState == EAIState::Alerted)	// If we are alerted we dont want to bother with noices
		return;

	SetGuardState(EAIState::Sus);
	
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Orange, false, 10.f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrinatation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrinatation, this, &AAIGuard::ResetOrinetation, 3.0f);
	
	StopMovement();
}

void AAIGuard::ResetOrinetation()
{
	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

	if(bAllowToPatrol)		// Guard returns to patrolling after being distracted
		MoveToNextPartolPoint();
}

void AAIGuard::SetGuardState(EAIState NewState)
{
	if(GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnStateChange(NewState);
}

void AAIGuard::MoveToNextPartolPoint()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)	// I know, i know this code is garbage 
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

void AAIGuard::StopMovement()
{
	AController* Controller = GetController();
	if(Controller)
	{
		Controller->StopMovement();
	}
}

void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	SensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	SensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiceHeard);

	OriginalRotation = GetActorRotation();

	if(bAllowToPatrol)
	{
		MoveToNextPartolPoint();
	}
}

void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToPatrolPoint = Delta.Size();	// Gets length of the vector

		if(DistanceToPatrolPoint < 100)	// If Gaurd is very close to patrol point he switches to the next one
		{
			MoveToNextPartolPoint();
		}
	}
}