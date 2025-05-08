// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemyController.h"
#include "NavigationSystem.h"
#include "../MainCharacter/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	NavigationMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	RandomPatrol();
	RunAwayFromPlayer();
}

void AAI_EnemyController::RandomPatrol()
{
	GetWorld()->GetTimerManager().SetTimer(PointDelay, this, &AAI_EnemyController::RandomPatrol, 3.f);
	
	if (NavigationMesh)
	{
		NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),
			RandomLocation, 1500.f);
		
		MoveToLocation(RandomLocation);
	}
}

void AAI_EnemyController::RunAwayFromPlayer()
{
	GetWorld()->GetTimerManager().SetTimer(RunAway, this, &AAI_EnemyController::RunAwayFromPlayer, 1.f,
		true, -1.f);

	const FVector PawnLocation = GetPawn()->GetActorLocation();
	const AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),
		0));

	const FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	const FVector RightVector = PlayerCharacter->GetActorRightVector();

	FVector WhereToMove = PawnLocation + ForwardVector + 700.f + RightVector + 700.f;

	// Рассчитать дистанцию от врага к нашему игроку
	const float Distance = GetPawn()->GetDistanceTo(PlayerCharacter);

	if (NavigationMesh && Distance < 700.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "RunAwayFromPlayer");
		NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),
			WhereToMove, 1500.f);
		ClearTimer();
	}
}

void AAI_EnemyController::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PointDelay);
	RandomPatrol();
}
