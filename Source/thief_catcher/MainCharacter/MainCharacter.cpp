#include "MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	if (Stamina > 100)
		Stamina = 100;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TouchEnemy();

	if (bIsSprinting && Stamina > 0.f)
		DecreaseStamina();
	else if (!bIsSprinting && Stamina < 100.f)
		IncreaseStamina();

	if (Stamina <= 0.f)
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
	if (GetCharacterMovement()->IsFalling())
		return;
	
	// Задержка прыжка для совпадения с анимацией
	GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &AMainCharacter::ExecuteJump,
		0.3f, false);

	if (JumpAnimMontage)
		PlayAnimMontage(JumpAnimMontage, 1.0, NAME_None);
	else
		UE_LOG(LogTemp, Fatal, TEXT("Failed to PlayAnimMontage!"));
}

void AMainCharacter::ExecuteJump()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		Super::Jump();
		bPressedJump = true;
	}
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
	bPressedJump = false;

	// Отменяем запланированный прыжок, если игрок отпустил кнопку
	if (GetWorld()->GetTimerManager().IsTimerActive(JumpTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
	}
}

void AMainCharacter::Sprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWithStamina;
	DecreaseStamina();
}

void AMainCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedWithoutStamina;
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
	const FVector TraceEnd = TraceStart + (CharacterRotation.Vector() * DistanceForTouchingEnemy);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (bShowDebugMessages)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0,
				  1);
	}

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	
	if (HitResult.bBlockingHit && HitResult.GetActor())
	{
		if (bShowDebugMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue,
			FString::Printf(TEXT("You hit: %s"), *HitResult.GetActor()->GetName()));
		}

		AActor* Target = HitResult.GetActor();
		if (Target && Target->ActorHasTag("Thief"))
		{
			if (bShowDebugMessages)
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Magenta, "Win win !!!");

			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
			
			// UKismetSystemLibrary::QuitGame(this,
			// 	UGameplayStatics::GetPlayerController(this, 0),
			// 	EQuitPreference::Quit, true);
		}
	}
}
