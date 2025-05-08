// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoxSpawner.generated.h"

UCLASS()
class THIEF_CATCHER_API ABoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void SpawnActor() const;

	UPROPERTY()
	UBoxComponent* BoxSpawner;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpawnerClass;

	UPROPERTY(EditDefaultsOnly)
	int NumberSpawnObjects;

	UPROPERTY(EditDefaultsOnly)
	bool bShouldSpawnLoop;
};
