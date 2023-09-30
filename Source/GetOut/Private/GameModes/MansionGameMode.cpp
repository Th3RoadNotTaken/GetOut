// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MansionGameMode.h"
#include "HUD/ProtagonistHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Protagonist.h"
#include "PlayerControllers/ProtagonistPlayerController.h"
#include "GameFramework/PlayerStart.h"

void AMansionGameMode::BeginPlay()
{
	Super::BeginPlay();
	Lives = MaxLives;
	Keys = MaxKeys;
}

void AMansionGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;
}

void AMansionGameMode::UpdateGameState(AProtagonistPlayerController* PlayerController, AProtagonist* ProtagonistCharacter)
{
	if (!PlayerController || ProtagonistCharacter == nullptr || ProtagonistCharacterClass == nullptr)return;

	AActor* LastPlayerActor = ProtagonistCharacter;
	ProtagonistCharacter->Destroy();

	if (Lives > 1)
	{
		PlayerController->UpdateLives(--Lives);
		if (bHasNoCheckpoints == true)
		{
			RestartPlayerAtPlayerStart(PlayerController, LastPlayerActor);
		}
		else
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				World->SpawnActor<AProtagonist>(ProtagonistCharacterClass, LastCheckpointTransform, SpawnParams);
			}
		}
	}
	else
	{
		RestartGame();
	}
}

void AMansionGameMode::ReduceKeysLeft()
{
	Keys = FMath::Clamp(Keys - 1, 0, MaxKeys);
}

void AMansionGameMode::SetLastCheckpoint(FTransform CheckpointTransform)
{
	bHasNoCheckpoints = false;
	LastCheckpointTransform = CheckpointTransform;
}