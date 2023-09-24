// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ProtagonistHUD.h"
#include "HUD/FadeWidget.h"

void AProtagonistHUD::AddFadeWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && FadeWidgetClass)
	{
		FadeWidget = CreateWidget<UFadeWidget>(PlayerController, FadeWidgetClass);
		FadeWidget->AddToViewport(0);
	}
}

void AProtagonistHUD::PlayFadeAnimation(bool bFadeIn)
{
	if (FadeWidget && FadeWidget->FadeIn)
	{
		if (bFadeIn)
			FadeWidget->PlayAnimation(FadeWidget->FadeIn);
		else
			FadeWidget->PlayAnimationReverse(FadeWidget->FadeIn);
	}
}