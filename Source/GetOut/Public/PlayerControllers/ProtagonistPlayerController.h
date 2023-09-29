// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProtagonistPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API AProtagonistPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	void UpdateGameTimer(float Time);
	void UpdateLives(int32 Lives);
	void UpdateKeys(int32 Keys);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class AProtagonistHUD* ProtagonistHUD;
	UPROPERTY()
	class AMansionGameMode* MansionGameMode;
	
};
