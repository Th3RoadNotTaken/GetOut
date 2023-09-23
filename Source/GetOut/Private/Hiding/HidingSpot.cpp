// Fill out your copyright notice in the Description page of Project Settings.


#include "Hiding/HidingSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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
}

void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();
}

void AHidingSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		}
		else
		{
			Character->SetActorTransform(OutsideRef->GetComponentTransform());
			Door->SetRelativeRotation(FRotator(0.f, 120.f, 0.f));
			bIsHiding = false;
		}
	}
}