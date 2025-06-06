// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	NumberSpawnObjects = 5;
	BoxSpawner = CreateDefaultSubobject<UBoxComponent>("Box Spawner");
	BoxSpawner->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SpawnDelay;
	GetWorldTimerManager().SetTimer(SpawnDelay, this, &ABoxSpawner::SpawnActor, SpawnInterval,
		bShouldSpawnLoop, InitialDelay);
}

void ABoxSpawner::SpawnActor() const
{
	for (int i = 0; i < NumberSpawnObjects; i++)
	{
		FRotator Rotation(0, 0, 0);
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),
			BoxSpawner->GetScaledBoxExtent());
		GetWorld()->SpawnActor<AActor>(SpawnerClass, RandomLocation, Rotation);
	}
}
