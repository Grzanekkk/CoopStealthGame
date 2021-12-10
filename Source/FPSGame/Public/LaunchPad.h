// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* OverlapComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	class UParticleSystem* LaunchFX;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchAxis;
	
	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
