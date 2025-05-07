#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float ABaseCharacter::GetStaminaPercentage() const
{
	return Stamina;
}

bool ABaseCharacter::StaminaIsZero()
{
	if (Stamina <= 0)
	{
		bIsTired = true;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UGameplayStatics::SpawnSoundAtLocation(this, TiredSound, GetActorLocation(), GetActorRotation());

	return bIsTired;
}

float ABaseCharacter::AddStaminaPercentage()
{
	return 0.0f;
}

float ABaseCharacter::DecreaseStaminaPercentage()
{
	return 0.0f;
}

