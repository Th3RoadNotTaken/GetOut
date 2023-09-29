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

	ProtagonistCharacter->Reset();
	ProtagonistCharacter->Destroy();

	if (Lives > 1)
	{
		PlayerController->UpdateLives(--Lives);
		if (LastCheckpoint == nullptr && CharacterPlayerStartClass)
		{
			TArray<AActor*> PlayerStarts;
			UGameplayStatics::GetAllActorsOfClass(this, CharacterPlayerStartClass, PlayerStarts);
			if (PlayerStarts.Num() > 0)
			{
				int32 RandIndex = FMath::RandRange(0, PlayerStarts.Num() - 1);
				RestartPlayerAtPlayerStart(PlayerController, PlayerStarts[RandIndex]);
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