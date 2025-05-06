// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "ThiefCatcher.h"
#include "Kismet/GameplayStatics.h"
#include "AI_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	class UNavigationSystemV1* NavigationMesh;

	FVector RandomLocation;

	UFUNCTION(BlueprintCallable)
	void RandomPatrol();

	// AActor* Enemy = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy::StaticClass());
	// AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(), AThiefCatcher::StaticClass());

	FTimerHandle RunAway;
	FTimerHandle PointDelay;

	bool bPlayerIsNear;

	UFUNCTION(BlueprintCallable)
	void RunAwayFromPlayer();

	UFUNCTION(BlueprintCallable)
	void ClearTimer();
	
};
