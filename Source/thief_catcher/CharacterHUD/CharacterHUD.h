// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public:

	ACharacterHUD();
	
private:

	virtual void BeginPlay() override;
	
	TSubclassOf<class UUserWidget> MainHUD;
	
};
