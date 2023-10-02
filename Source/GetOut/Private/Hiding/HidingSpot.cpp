// Fill out your copyright notice in the Description page of Project Settings.


#include "Hiding/HidingSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "HUD/InteractWidget.h"
#include "Sound/SoundAttenuation.h"
#include "Sound/SoundCue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AHidingSpot::AHidingSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	DoorFrame->SetupAttachment(GetRootComponent());
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	InsideRef = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Inside Reference"));
	InsideRef->SetupAttachment(GetRootComponent());
	InsideRef->bHiddenInGame = true;
	InsideRef->SetVisibility(false);

	OutsideRef = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outside Reference"));
	OutsideRef->SetupAttachment(GetRootComponent());
	OutsideRef->bHiddenInGame = true;
	OutsideRef->SetVisibility(false);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(GetRootComponent());

	GuardTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Guard Trigger Box"));
	GuardTriggerBox->SetupAttachment(GetRootComponent());

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget Component"));
	InteractionWidgetComponent->SetupAttachment(GetRootComponent());
}

void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
		UUserWidget* Widget = InteractionWidgetComponent->GetWidget();
		if (Widget)
		{
			InteractWidget = Cast<UInteractWidget>(Widget);
		}
	}
}

void AHidingSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldOpenDoor)
	{
		FRotator DeltaRotation;
		FRotator StartingRotation = Door->GetRelativeRotation();
		FRotator EndingRotation = FRotator(0.f, 120.f, 0.f);
		DeltaRotation = FMath::RInterpTo(StartingRotation, EndingRotation, DeltaTime, 2.f);
		Door->SetRelativeRotation(DeltaRotation);
		
		if (DeltaRotation.Yaw >= (EndingRotation.Yaw - 10.f))
		{
			bShouldOpenDoor = false;
			Door->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
}

void AHidingSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (InteractionWidgetComponent == nullptr || InteractWidget == nullptr || OtherActor!=UGameplayStatics::GetPlayerCharacter(this,0))
		return;

	bIsOverlapping = true;
	FString HidingText;
	if (!bIsHiding)
	{
		HidingText = "Press E To Hide";
	}
	else
	{
		HidingText = "Press E To Get Out";
	}
	InteractWidget->UpdateInteractionText(HidingText);
	InteractionWidgetComponent->SetVisibility(true);
}

void AHidingSpot::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlapping = false;
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
	}
}

void AHidingSpot::InteractWithObject()
{
	if (!bIsOverlapping)return;

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character)
	{
		FHitResult OutHit;
		if (!bIsHiding)
		{
			Character->SetActorTransform(InsideRef->GetComponentTransform());
			Character->GetCapsuleComponent()->SetCapsuleRadius(44.f);
			Character->GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = false;
			Door->SetRelativeRotation(FRotator(0.f));
			bIsHiding = true;
			PlayInteractSound(EnterSound);
		}
		else
		{
			Character->SetActorTransform(OutsideRef->GetComponentTransform());
			Character->GetCapsuleComponent()->SetCapsuleRadius(65.f);
			Character->GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
			Door->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));
			bIsHiding = false;
			PlayInteractSound(ExitSound);
		}
	}
}

void AHidingSpot::PlayInteractSound(USoundCue* Sound)
{
	if (Sound && InteractAttenuation)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			Sound,
			GetActorLocation(),
			1.f,
			1.f,
			0.f,
			InteractAttenuation
		);
	}
}

void AHidingSpot::OpenDoor()
{
	if (bIsHiding)
	{
		bShouldOpenDoor = true;
		Door->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}