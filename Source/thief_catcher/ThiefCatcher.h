#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ThiefCatcher.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API AThiefCatcher : public AMainCharacter
{
	GENERATED_BODY()

public:
	AThiefCatcher();

private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
