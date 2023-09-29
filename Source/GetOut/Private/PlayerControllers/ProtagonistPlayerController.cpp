// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/ProtagonistPlayerController.h"
#include "HUD/ProtagonistHUD.h"
#include "GameModes/MansionGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/ProtagonistOverlay.h"

void AProtagonistPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	MansionGameMode = MansionGameMode == nullptr ? Cast<AMansionGameMode>(UGameplayStatics::GetGameMode(this)) : MansionGameMode;
}

void AProtagonistPlayerController::Tick(float DeltaTime)
{
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	MansionGameMode = MansionGameMode == nullptr ? Cast<AMansionGameMode>(UGameplayStatics::GetGameMode(this)) : MansionGameMode;
	if (ProtagonistHUD)
	{
		UpdateGameTimer(MansionGameMode->GetGameTime());
	}
}

void AProtagonistPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	if (ProtagonistHUD)
	{
		ProtagonistHUD->PlayFadeAnimation(true);
	}
}

void AProtagonistPlayerController::UpdateGameTimer(float Time)
{
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	bool bIsHUDValid =
		ProtagonistHUD &&
		ProtagonistHUD->OverlayWidget;

	if (bIsHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(Time / 60.f);
		int32 Seconds = Time - Minutes * 60.f;
		FString TimerText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

		ProtagonistHUD->OverlayWidget->UpdateTimerText(TimerText);
	}
}

void AProtagonistPlayerController::UpdateLives(int32 Lives)
{
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	bool bIsHUDValid =
		ProtagonistHUD &&
		ProtagonistHUD->OverlayWidget;

	if (bIsHUDValid)
	{
		FString LivesText = FString::Printf(TEXT("%d"), Lives);
		ProtagonistHUD->OverlayWidget->UpdateLivesText(LivesText);
	}
}

void AProtagonistPlayerController::UpdateKeys(int32 Keys)
{
	ProtagonistHUD = ProtagonistHUD == nullptr ? Cast<AProtagonistHUD>(GetHUD()) : ProtagonistHUD;
	bool bIsHUDValid =
		ProtagonistHUD &&
		ProtagonistHUD->OverlayWidget;

	if (bIsHUDValid)
	{
		FString KeysText = FString::Printf(TEXT("%d"), Keys);
		ProtagonistHUD->OverlayWidget->UpdateKeysText(KeysText);
	}
}