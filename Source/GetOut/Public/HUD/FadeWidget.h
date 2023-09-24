// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	void PlayFadeAnimation(bool bFadeIn);
	
};
