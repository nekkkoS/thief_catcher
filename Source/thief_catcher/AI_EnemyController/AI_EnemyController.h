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
	
	UPROPERTY()
	class UNavigationSystemV1* NavigationMesh;

	// Задержка (в секундах) между выбором следующей случайной точки патрулирования
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float PatrolPointDelay = 2.f;

	// Максимальный радиус, в пределах которого ИИ ищет новую точку для патрулирования
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float PatrolRandomLocationRadius = 5000.f;

	// Частота обновления побега (в секунду)
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float RunAwayUpdateInterval = 2.0f;  

	// Минимальная дистанция для побега
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float MinRunAwayDistance = 3000.0f;  

	// Отступ от игрока при побеге
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float RunAwayOffset = 4000.0f;  

	// Радиус поиска точки для побега 
	UPROPERTY(EditDefaultsOnly, Category = AI, meta=(ClampMin = 0))
	float RunAwaySearchRadius = 7000.0f; 

	FVector RandomLocation;

	FTimerHandle RunAway;
	
	FTimerHandle PointDelay;

	bool bPlayerIsNear;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
	bool bShowDebugMessages = false;
	
};
