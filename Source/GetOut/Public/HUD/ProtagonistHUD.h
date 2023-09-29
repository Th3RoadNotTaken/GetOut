// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProtagonistHUD.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API AProtagonistHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> FadeWidgetClass;

	UPROPERTY()
	class UFadeWidget* FadeWidget;

	void AddFadeWidget();
	void PlayFadeAnimation(bool bFadeIn);

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY()
	class UProtagonistOverlay* OverlayWidget;

	void AddOverlayWidget();
	
};
