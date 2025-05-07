// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetStamina.h"
#include "../MainCharacter/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

float UUserWidgetStamina::GetCharacterStamina()
{
	const AMainCharacter* OurPlayer = Cast<AMainCharacter>
	(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	return OurPlayer->GetStamina() / 100.0f;
}
