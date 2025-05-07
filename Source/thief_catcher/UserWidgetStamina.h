// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetStamina.generated.h"

class AMainCharacter;

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API UUserWidgetStamina : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCharacterStamina();
	
};
