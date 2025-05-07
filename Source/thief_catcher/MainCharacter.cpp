#include "MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AMainCharacter::AMainCharacter() : Super()
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

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainCharacter::MoveRightLeft);

	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpDown", this, &AMainCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprint);
}

void AMainCharacter::MoveForwardBackward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::MoveRightLeft(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::Jump()
{
	Super::Jump();
	bPressedJump = true;

	if (JumpAnimMontage)
		PlayAnimMontage(JumpAnimMontage, 1.0, NAME_None);
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
	bPressedJump = false;
}

float AMainCharacter::GetStamina() const
{
	return Stamina;
}

void AMainCharacter::AddStamina_Implementation(float AddStamina)
{
	IInteractInterface::AddStamina_Implementation(AddStamina);
	Stamina += AddStamina;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TouchEnemy();

	if (bIsSprinting && Stamina > 0.f)
		DecreaseStamina();
	else if (!bIsSprinting && Stamina < 100.f)
		IncreaseStamina();

	if (FMath::IsNearlyZero(Stamina))
		StopSprint();
}

void AMainCharacter::Sprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	DecreaseStamina();
}

void AMainCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	IncreaseStamina();
}

void AMainCharacter::IncreaseStamina()
{
	Stamina += PlusStamina;
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	//                                  FString::Printf(TEXT("Stamina: %f"), Stamina));
}

void AMainCharacter::DecreaseStamina()
{
	Stamina -= MinusStamina;
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	//                                  FString::Printf(TEXT("Stamina: %f"), Stamina));
}

void AMainCharacter::TouchEnemy()
{
	FVector TraceStart = GetActorLocation();
	FRotator CharacterRotation = GetActorRotation();
	FVector TraceEnd = TraceStart + (CharacterRotation.Vector() * 700.f);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0,
	              1);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility,
		QueryParams);

	if (HitResult.bBlockingHit && HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue,
			FString::Printf(TEXT("You hitted: %s"), *HitResult.GetActor()->GetName()));

		AActor* Target = HitResult.GetActor();
		if (Target && Target->ActorHasTag("Thief"))
		{
			// UKismetSystemLibrary::QuitGame(this,
			// 	UGameplayStatics::GetPlayerController(this, 0),
			// 	EQuitPreference::Quit, true);
		}
	}
}
