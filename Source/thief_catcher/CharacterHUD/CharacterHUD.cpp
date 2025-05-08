// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"

#include "Blueprint/UserWidget.h"

ACharacterHUD::ACharacterHUD() : Super()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> WBP_Stamina(TEXT("/Game/Widgets/WBP_Stamina"));
	MainHUD = WBP_Stamina.Class;
}

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (UUserWidget* CharacterWidget = CreateWidget(GetWorld(), MainHUD))
		CharacterWidget->AddToViewport();
}
