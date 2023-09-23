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

public:	

};
