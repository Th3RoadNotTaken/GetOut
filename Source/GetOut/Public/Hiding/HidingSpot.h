// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interact.h"
#include "HidingSpot.generated.h"

UCLASS()
class GETOUT_API AHidingSpot : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	AHidingSpot();
	virtual void Tick(float DeltaTime) override;
	virtual void InteractWithObject() override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* InsideRef;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* OutsideRef;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	bool bIsHiding = false;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	class UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	class AProtagonistHUD* CharacterHUD;

	UPROPERTY()
	class UInteractWidget* InteractWidget;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundCue* EnterSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundCue* ExitSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundAttenuation* InteractAttenuation;

	void PlayInteractSound(USoundCue* Sound);

public:	

};
