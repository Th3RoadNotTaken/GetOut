// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Protagonist.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Interact.h"
#include "HUD/ProtagonistHUD.h"
#include "GameFramework/CharacterMovementComponent.h"

AProtagonist::AProtagonist()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), FName("Head"));

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(Camera);
	Flashlight->SetVisibility(false);
}

void AProtagonist::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(ProtagonistMappingContext, 0);
		}
	}
	Tags.Add(FName("Player"));
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()) : ProtagonistHUD;
	if (ProtagonistHUD)
	{
		ProtagonistHUD->AddFadeWidget();
		ProtagonistHUD->PlayFadeAnimation(true);
	}
	if (StartGameSound)
	{
		UGameplayStatics::PlaySound2D(this, StartGameSound);
	}

	OnTakeAnyDamage.AddDynamic(this, &ThisClass::ReceiveDamage);
}

void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProtagonist::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProtagonist::Look);
		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AProtagonist::FlashlightKeyPressed);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AProtagonist::InteractKeyPressed);
	}
}

void AProtagonist::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);

	FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MovementVector.X);
	AddMovementInput(Right, MovementVector.Y);
}

void AProtagonist::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AProtagonist::InteractKeyPressed()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(
		OverlappingActors
	);
	if (OverlappingActors.Num() == 0)return;

	for (auto Actor : OverlappingActors)
	{
		if (Actor)
		{
			IInteract* InteractInterface = Cast<IInteract>(Actor);
			if (InteractInterface)
			{
				InteractInterface->InteractWithObject();
			}
		}
	}
}

void AProtagonist::FlashlightKeyPressed()
{
	if (bFlashlightTimerFinished)
	{
		bFlashlightTimerFinished = false;
		GetWorldTimerManager().SetTimer(
			FlashlightTimerHandle,
			this,
			&AProtagonist::UpdateFlashlightState,
			FlashlightSwitchDelay
		);
	}
}

void AProtagonist::UpdateFlashlightState()
{
	bFlashlightTimerFinished = true;
	if (!bIsFlashlightOn)
	{
		Flashlight->SetVisibility(true);
		bIsFlashlightOn = true;
	}
	else
	{
		Flashlight->SetVisibility(false);
		bIsFlashlightOn = false;
	}

	if (FlashlightClickSound)
	{
		UGameplayStatics::PlaySound2D(
			this,
			FlashlightClickSound
		);
	}
}

void AProtagonist::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();

	if (ProtagonistHUD)
	{
		ProtagonistHUD->PlayFadeAnimation(false);
	}
	if (JumpScareSound)
	{
		UGameplayStatics::PlaySound2D(this, JumpScareSound);
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			UGameplayStatics::OpenLevel(this, FName("Testing"));
		}, 1.f, false);
}