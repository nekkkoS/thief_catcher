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

	// Класс для спавна
	UPROPERTY(EditDefaultsOnly, Category=Spawn)
	TSubclassOf<AActor> SpawnerClass;

	// Количество объектов для спавна за раз
	UPROPERTY(EditDefaultsOnly, Category=Spawn)
	int NumberSpawnObjects;

	// Нужно ли спавнить в цикле
	UPROPERTY(EditDefaultsOnly, Category=Spawn)
	bool bShouldSpawnLoop;

	// Задержка перед первым спавном
	UPROPERTY(EditDefaultsOnly, Category=Spawn)
	float InitialDelay = 1.0f;

	// Интервал между спавнами
	UPROPERTY(EditDefaultsOnly, Category=Spawn)
	float SpawnInterval = 1.0f;
	
};
