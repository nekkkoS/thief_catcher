#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractInterface.h"
#include "ThiefCatcher.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API AThiefCatcher : public AMainCharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	AThiefCatcher();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float Value);
	
	void MoveRightLeft(float Value);

	virtual void Jump() override;

	virtual void StopJumping() override;

	float GetStamina() const;

	virtual void AddStamina_Implementation(float AddStamina) override;

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JumpAnimation)
	UAnimMontage* JumpAnimMontage;

private:

	virtual void Tick(float DeltaTime) override;

	void Sprint();

	void StopSprint();

	void IncreaseStamina();

	void DecreaseStamina();

	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float MinusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float PlusStamina = 1.0f;

	bool bIsSprinting;

};
