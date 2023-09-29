// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProtagonistOverlay.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API UProtagonistOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LivesText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KeysText;
	
	void UpdateTimerText(FString Text);
	void UpdateLivesText(FString Text);
	void UpdateKeysText(FString Text);
};
