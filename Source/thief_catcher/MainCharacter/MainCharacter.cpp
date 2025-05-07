#include "MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter() : Super()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	if (!SpringArm)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to create SpringArmComponent!"));
		return;
	}
	
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	if (!Camera)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to create MainCamera!"));
		return;
	}
	
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
}

float AMainCharacter::GetStamina() const
{
	return Stamina;
}

void AMainCharacter::AddStamina_Implementation(const float AdditionalStamina)
{
	IInteractInterface::AddStamina_Implementation(AdditionalStamina);
	Stamina += AdditionalStamina;
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

void AMainCharacter::MoveForwardBackward(const float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::MoveRightLeft(const float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::Jump()
{
	Super::Jump();
	bPressedJump = true;

	if (JumpAnimMontage)
		PlayAnimMontage(JumpAnimMontage, 1.0, NAME_None);
	else
		UE_LOG(LogTemp, Fatal, TEXT("Failed to PlayAnimMontage!"));
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
	bPressedJump = false;
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
}

void AMainCharacter::DecreaseStamina()
{
	Stamina -= MinusStamina;
}

void AMainCharacter::TouchEnemy() const
{
	const FVector TraceStart = GetActorLocation();
	const FRotator CharacterRotation = GetActorRotation();
	constexpr float DistanceForTouching{70.f};
	const FVector TraceEnd = TraceStart + (CharacterRotation.Vector() * DistanceForTouching);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0,
	              1);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	
	if (HitResult.bBlockingHit && HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue,
			FString::Printf(TEXT("You hitted: %s"), *HitResult.GetActor()->GetName()));

		AActor* Target = HitResult.GetActor();
		if (Target && Target->ActorHasTag("Thief"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Magenta, "Win win !!!");
			// UKismetSystemLibrary::QuitGame(this,
			// 	UGameplayStatics::GetPlayerController(this, 0),
			// 	EQuitPreference::Quit, true);
		}
	}
}
