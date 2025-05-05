// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemyController.h"
#include "NavigationSystem.h"

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	NavigationMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	RandomPatrol();
}

void AAI_EnemyController::RandomPatrol()
{
	if (NavigationMesh)
	{
		NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),
			RandomLocation, 1500.f);
		MoveToLocation(RandomLocation);

		FTimerHandle PointDelay;
		GetWorld()->GetTimerManager().SetTimer(PointDelay, this, &AAI_EnemyController::RandomPatrol, 3.f);
	}
}
