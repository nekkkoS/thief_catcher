// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyDrink.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnergyDrink::AEnergyDrink()
{
	PrimaryActorTick.bCanEverTick = false;
	
 	DrinkStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrinkStaticMesh"));
	DrinkStaticMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	DrinkStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnergyDrink::Overlap);
	
	const ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Game/Spawners/EnergyDrink/DrinkSound"));
	DrinkSound = Sound.Object.Get();
}

void AEnergyDrink::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractInterface::Execute_AddStamina(OtherActor, AdditionalStaminaByDrink);
	
	// TODO: Фиксануть рангдомное воспроизвеедение звука
	UGameplayStatics::PlaySoundAtLocation(this, DrinkSound, GetActorLocation(),
		0.5f, 1, 0);
	
	Destroy();
}

