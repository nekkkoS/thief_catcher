#include "ThiefCatcher.h"

AThiefCatcher::AThiefCatcher() : Super()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	Camera->SetupAttachment(SpringArm);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
}

void AThiefCatcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AThiefCatcher::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &AThiefCatcher::MoveRightLeft);
	
	PlayerInputComponent->BindAxis("Turn", this, &AThiefCatcher::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpDown", this, &AThiefCatcher::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThiefCatcher::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AThiefCatcher::StopJumping);
}

void AThiefCatcher::MoveForwardBackward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AThiefCatcher::MoveRightLeft(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AThiefCatcher::Jump()
{
	Super::Jump();
	bPressedJump = true;

	if (JumpAnimMontage)
		PlayAnimMontage(JumpAnimMontage, 1.0, NAME_None);
}

void AThiefCatcher::StopJumping()
{
	Super::StopJumping();
	bPressedJump = false;
}
