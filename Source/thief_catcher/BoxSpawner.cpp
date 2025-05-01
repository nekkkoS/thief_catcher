// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
	SpawnObjectsCount = 5;
	BoxSpawner = CreateDefaultSubobject<UBoxComponent>("Box Spawner");
	BoxSpawner->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SpawnDelay;
	GetWorldTimerManager().SetTimer(SpawnDelay, this, &ABoxSpawner::SpawnActor, 1, bShouldSpawnLoop,
	                                1);
}

void ABoxSpawner::SpawnActor() const
{
	for (int i = 0; i < SpawnObjectsCount; i++)
	{
		FRotator Rotation(0, 0, 0);
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),
			BoxSpawner->GetScaledBoxExtent());
		GetWorld()->SpawnActor<AActor>(SpawnerClass, RandomLocation, Rotation);
	}
}
