// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetStamina.h"
#include "ThiefCatcher.h"
#include "Kismet/GameplayStatics.h"

float UUserWidgetStamina::GetCharacterStamina()
{
	const AThiefCatcher* OurPlayer = Cast<AThiefCatcher>
	(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	return OurPlayer->GetStamina() / 100.0f;
}
