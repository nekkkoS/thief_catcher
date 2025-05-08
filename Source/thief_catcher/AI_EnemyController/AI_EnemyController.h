// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION(BlueprintCallable)
	void RandomPatrol();

	UFUNCTION(BlueprintCallable)
	void RunAwayFromPlayer();

	UFUNCTION(BlueprintCallable)
	void ClearTimer();

	UPROPERTY(Transient)
	class UNavigationSystemV1* NavigationMesh;

	FVector RandomLocation;

	FTimerHandle RunAway;
	
	FTimerHandle PointDelay;

	bool bPlayerIsNear;
	
};
