#include "ThiefCatcher.h"

#include "GameFramework/CharacterMovementComponent.h"

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
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AThiefCatcher::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AThiefCatcher::StopSprint);
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

float AThiefCatcher::GetStamina() const
{
	return Stamina;
}

void AThiefCatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsSprinting && Stamina > 0.f)
		DecreaseStamina();
	else if (!bIsSprinting && Stamina < 100.f)
		IncreaseStamina();
	
	if (FMath::IsNearlyZero(Stamina))
		StopSprint();
}

void AThiefCatcher::Sprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	DecreaseStamina();
}

void AThiefCatcher::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	IncreaseStamina();
}

void AThiefCatcher::IncreaseStamina()
{
	Stamina += PlusStamina;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Stamina: %f"), Stamina));
}

void AThiefCatcher::DecreaseStamina()
{
	Stamina -= MinusStamina;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Stamina: %f"), Stamina));
}
