#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class THIEF_CATCHER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	float GetStaminaPercentage() const;
	bool StaminaIsZero();
	float AddStaminaPercentage();
	float DecreaseStaminaPercentage();

private:

	UPROPERTY(EditDefaultsOnly, Category="CharacterStamina")
	float Stamina = 100.0f;
	
	bool bIsTired = false;

	UPROPERTY(EditDefaultsOnly, Category="CharacterStamina")
	USoundBase* TiredSound;
	
	UPROPERTY(EditDefaultsOnly, Category="CharacterStamina")
	UAnimMontage* VertigoAnimMontage;
};
