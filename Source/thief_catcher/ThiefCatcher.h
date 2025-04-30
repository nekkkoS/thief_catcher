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

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float Value);
	
	void MoveRightLeft(float Value);

	void Jump() override;

	void StopJumping() override;

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JumpAnimation)
	UAnimMontage* JumpAnimMontage;
};
