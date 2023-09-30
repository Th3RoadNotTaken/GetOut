// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "HUD/InteractWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "PlayerControllers/ProtagonistPlayerController.h"
#include "GameModes/MansionGameMode.h"
#include "Sound/SoundCue.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(ItemMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Sphere"));
	OverlapSphere->SetupAttachment(RootComponent);

	IdleParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Idle Particles"));
	IdleParticles->SetupAttachment(RootComponent);

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget Component"));
	InteractionWidgetComponent->SetupAttachment(GetRootComponent());

	RefMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ref Mesh"));
	RefMesh->SetupAttachment(RootComponent);
	RefMesh->SetHiddenInGame(true);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBegin);
	OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereEnd);

	PlayerController = PlayerController == nullptr ? Cast<AProtagonistPlayerController>(UGameplayStatics::GetPlayerController(this, 0)) : PlayerController;
	MansionGameMode = MansionGameMode == nullptr ? Cast<AMansionGameMode>(UGameplayStatics::GetGameMode(this)) : MansionGameMode;

	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
		UUserWidget* Widget = InteractionWidgetComponent->GetWidget();
		if (Widget)
		{
			InteractWidget = Cast<UInteractWidget>(Widget);
			if (InteractWidget)
			{
				FString OverlapText = "Press E To Pick up";
				InteractWidget->UpdateInteractionText(OverlapText);
			}
		}
	}
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnOverlapSphereBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (InteractionWidgetComponent == nullptr || InteractWidget == nullptr || OtherActor != UGameplayStatics::GetPlayerCharacter(this, 0))
		return;

	InteractionWidgetComponent->SetVisibility(true);
}

void APickup::OnOverlapSphereEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractionWidgetComponent == nullptr || InteractWidget == nullptr || OtherActor != UGameplayStatics::GetPlayerCharacter(this, 0))
		return;

	InteractionWidgetComponent->SetVisibility(false);
}

void APickup::InteractWithObject()
{
	PlayerController = PlayerController == nullptr ? Cast<AProtagonistPlayerController>(UGameplayStatics::GetPlayerController(this, 0)) : PlayerController;
	MansionGameMode = MansionGameMode == nullptr ? Cast<AMansionGameMode>(UGameplayStatics::GetGameMode(this)) : MansionGameMode;
	if (PlayerController == nullptr || MansionGameMode == nullptr || RefMesh == nullptr)return;

	MansionGameMode->ReduceKeysLeft();
	MansionGameMode->SetLastCheckpoint(RefMesh->GetComponentTransform());

	PlayerController->UpdateKeys(MansionGameMode->GetKeysLeft());

	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(this, PickupSound);
	}
	Destroy();
}