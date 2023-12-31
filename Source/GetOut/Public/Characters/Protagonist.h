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
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

private:
	UPROPERTY()
	class AProtagonistHUD* ProtagonistHUD;
	UPROPERTY()
	class AMansionGameMode* MansionGameMode;
	UPROPERTY()
	class AProtagonistPlayerController* CharacterController;
	UPROPERTY(VisibleAnywhere, Category = "Character Components")
	class USpotLightComponent* Flashlight;
	UPROPERTY(VisibleAnywhere, Category = "Character Components")
	class USpringArmComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = "Character Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Character Components")
	class USoundCue* FlashlightClickSound;
	UPROPERTY(EditAnywhere, Category = "Character Components")
	USoundCue* StartGameSound;
	UPROPERTY(EditAnywhere, Category = "Character Components")
	USoundCue* JumpScareSound;
	UPROPERTY(EditAnywhere, Category = "Character Components")
	USoundCue* AmbientSound;
	UPROPERTY()
	UAudioComponent* AmbientSoundComponent;

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
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CrouchPressed();
	void InteractKeyPressed();
	void FlashlightKeyPressed();
	void UpdateFlashlightState();
	bool bFlashlightTimerFinished = true;
	bool bIsFlashlightOn = false;
	UPROPERTY(EditAnywhere, Category = "Character Components")
	float FlashlightSwitchDelay = 0.3f;
	FTimerHandle FlashlightTimerHandle;

public:	
	FORCEINLINE bool IsCrouching() const { return bIsCrouched; }
};
