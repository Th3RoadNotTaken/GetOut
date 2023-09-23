// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Protagonist.generated.h"

UCLASS()
class GETOUT_API AProtagonist : public ACharacter
{
	GENERATED_BODY()

public:
	AProtagonist();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USpotLightComponent* Flashlight;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	/**
	* Input
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* ProtagonistMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FlashlightAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void UpdateFlashlightState();
	bool bIsFlashlightOn = false;

public:	

};
