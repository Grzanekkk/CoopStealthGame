// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALaunchPad::ALaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;
	
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Component"));
	OverlapComp->SetBoxExtent(FVector(75,75, 50));
	RootComponent = OverlapComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(RootComponent);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);

	LaunchStrength = 1500.f;
	LaunchPitchAngle = 45.f;
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if(OtherCharacter)		// Allows launching Characters
	{
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
	else if(OtherComp && OtherComp->IsSimulatingPhysics()) // Allows launching Physics props 
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
}