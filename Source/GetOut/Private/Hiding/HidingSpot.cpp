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

AHidingSpot::AHidingSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = DoorFrame;
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
}

void AHidingSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (InteractionWidgetComponent == nullptr || InteractWidget == nullptr || OtherActor!=UGameplayStatics::GetPlayerCharacter(this,0))
		return;

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
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
	}
}

void AHidingSpot::InteractWithObject()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character)
	{
		FHitResult OutHit;
		if (!bIsHiding)
		{
			Character->SetActorTransform(InsideRef->GetComponentTransform());
			Door->SetRelativeRotation(FRotator(0.f));
			bIsHiding = true;
			PlayInteractSound(EnterSound);
		}
		else
		{
			Character->SetActorTransform(OutsideRef->GetComponentTransform());
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