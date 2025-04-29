#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AMainCharacter::GetStaminaPercentage() const
{
	return Stamina;
}

bool AMainCharacter::StaminaIsZero()
{
	if (Stamina <= 0)
	{
		bIsTired = true;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UGameplayStatics::SpawnSoundAtLocation(this, TiredSound, GetActorLocation(), GetActorRotation());

	return bIsTired;
}

float AMainCharacter::AddStaminaPercentage()
{
	return 0.0f;
}

float AMainCharacter::DecreaseStaminaPercentage()
{
	return 0.0f;
}

