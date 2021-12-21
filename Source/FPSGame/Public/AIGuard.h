// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"

UENUM()
enum class EAIState : uint8
{
	Idle,
	Sus,
	Alerted
};


UCLASS()
class FPSGAME_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Componenets")
	class UPawnSensingComponent* SensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiceHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrinetation();
	
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState NewState);

	void MoveToNextPartolPoint();

	
	FRotator OriginalRotation;
	
	FTimerHandle TimerHandle_ResetOrinatation;

	EAIState GuardState;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bAllowToPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bAllowToParol"))	// I know it should be an array 
	AActor* FirstPatrolPoint;
	
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bAllowToParol"))
	AActor* SecondPatrolPoint;

	UPROPERTY()
	AActor* CurrentPatrolPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
