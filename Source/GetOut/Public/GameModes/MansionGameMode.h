// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MansionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API AMansionGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void UpdateGameState(class AProtagonistPlayerController* PlayerController, class AProtagonist* ProtagonistCharacter);
	void ReduceKeysLeft();
	virtual void Tick(float DeltaTime) override;
	void SetLastCheckpoint(FTransform CheckpointTransform);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	int32 MaxLives = 3;
	int32 Lives;
	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	int32 MaxKeys = 5;
	int32 Keys;
	
	float GameTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	FTransform LastCheckpointTransform;
	bool bHasNoCheckpoints = true;

	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	TSubclassOf<class AProtagonist> ProtagonistCharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	TSubclassOf<class AActor> CharacterPlayerStartClass;

public:
	FORCEINLINE float GetGameTime() const { return GameTime; }
	FORCEINLINE int32 GetKeysLeft() const { return Keys; }
};
