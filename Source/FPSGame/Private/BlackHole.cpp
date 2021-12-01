// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	DestructionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestructionSphere"));
	DestructionSphere->SetSphereRadius(100);
	DestructionSphere->SetupAttachment(MeshComp);

	DestructionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapDestructionSphere);

	SuckingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SuckingSphere"));
	SuckingSphere->SetSphereRadius(2500);
	SuckingSphere->SetupAttachment(MeshComp);
}

void ABlackHole::OverlapDestructionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlapingObjects;
	SuckingSphere->GetOverlappingComponents(OverlapingObjects);	// Only works on objects that may be physically simulated
	
	for (UPrimitiveComponent* OverlapingObject : OverlapingObjects)
	{
		if (OverlapingObject && OverlapingObject->IsSimulatingPhysics())
		{
			OverlapingObject->AddRadialForce(GetActorLocation(), SuckingSphere->GetScaledSphereRadius(), SuckingStrenght, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}

}

