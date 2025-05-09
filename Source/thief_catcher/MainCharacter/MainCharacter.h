#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../InteractInterface/InteractInterface.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THIEF_CATCHER_API AMainCharacter : public ABaseCharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	
	AMainCharacter();

	float GetStamina() const;

	virtual void AddStamina_Implementation(const float AdditionalStamina) override;

protected:

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JumpAnimation)
	UAnimMontage* JumpAnimMontage;

private:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(const float Value);
	
	void MoveRightLeft(const float Value);

	virtual void Jump() override;

	void ExecuteJump();

	virtual void StopJumping() override;

	void Sprint();

	void StopSprint();

	void IncreaseStamina();

	void DecreaseStamina();

	UFUNCTION()
	void TouchEnemy() const;

	UPROPERTY(EditDefaultsOnly, Category=Stamina, meta=(ClampMin = 0, ClampMax = 100))
	float Stamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category=Stamina, meta=(ClampMin = 0, ClampMax = 100))
	float MinusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category=Stamina, meta=(ClampMin = 0, ClampMax = 100))
	float PlusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float MaxWalkSpeedWithStamina = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category=Stamina)
	float MaxWalkSpeedWithoutStamina = 600.f;

	UPROPERTY(EditDefaultsOnly)
	float DistanceForTouchingEnemy = 70.f;

	bool bIsSprinting = false;

	FTimerHandle JumpTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
	bool bShowDebugMessages = true;

};
