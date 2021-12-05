// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"

#include "AABBTree.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Component"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(300.0f));
	OverlapComp->SetHiddenInGame(false);
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);


	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	DecalComp->DecalSize = FVector(300.f);
	DecalComp->SetupAttachment(RootComponent);

	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone!"));
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone!"));

	AFPSCharacter* OverlapingPlayer = Cast<AFPSCharacter>(OtherActor);

	if(OverlapingPlayer->bIsCarryingObjective)
	{
		
	}
}