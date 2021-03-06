// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

	UPROPERTY(EditAnywhere, Category = "Physics")
	float SuckingStrenght = -2000.f;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;
	
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* DestructionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SuckingSphere;

	// Finds overlapping actors and destroys them 
	UFUNCTION()
	void OverlapDestructionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
