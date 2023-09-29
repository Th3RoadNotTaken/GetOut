// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interact.h"
#include "Pickup.generated.h"

UCLASS()
class GETOUT_API APickup : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	APickup();
	virtual void Tick(float DeltaTime) override;
	virtual void InteractWithObject() override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnOverlapSphereBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapSphereEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Basic")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, Category = "Basic")
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere, Category = "Basic")
	class UParticleSystemComponent* IdleParticles;

	UPROPERTY(EditAnywhere, Category = "Basic")
	class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Basic")
	class USkeletalMeshComponent* RefMesh;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	class UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY()
	class UInteractWidget* InteractWidget;
	
	UPROPERTY()
	class AProtagonistPlayerController* PlayerController;
	UPROPERTY()
	class AMansionGameMode* MansionGameMode;

public:	

};
