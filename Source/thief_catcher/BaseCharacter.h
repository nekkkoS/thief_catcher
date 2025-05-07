#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class THIEF_CATCHER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	float GetStaminaPercentage() const;
	bool StaminaIsZero();
	float AddStaminaPercentage();
	float DecreaseStaminaPercentage();

protected:

	UPROPERTY(EditDefaultsOnly, Category=Stamina, meta=(ClampMin = 0, ClampMax = 100))
	float Stamina = 100.0f;
	
	bool bIsTired = false;

	UPROPERTY(EditDefaultsOnly, Category=CharacterStamina)
	USoundBase* TiredSound;
	
	UPROPERTY(EditDefaultsOnly, Category=CharacterStamina)
	UAnimMontage* VertigoAnimMontage;
};
