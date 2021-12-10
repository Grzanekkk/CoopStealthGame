// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "Components/BoxComponent.h"


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
	LaunchAxis = 45.f;
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}