// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ProtagonistOverlay.h"
#include "Components/TextBlock.h"

void UProtagonistOverlay::UpdateTimerText(FString Text)
{
	if (TimerText)
	{
		TimerText->SetText(FText::FromString(Text));
	}
}

void UProtagonistOverlay::UpdateLivesText(FString Text)
{
	if (LivesText)
	{
		LivesText->SetText(FText::FromString(Text));
	}
}

void UProtagonistOverlay::UpdateKeysText(FString Text)
{
	if (KeysText)
	{
		KeysText->SetText(FText::FromString(Text));
	}
}