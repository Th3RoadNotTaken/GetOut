// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FadeWidget.h"

void UFadeWidget::PlayFadeAnimation(bool bFadeIn)
{
	if (bFadeIn)
		PlayAnimation(FadeIn);
	else
		PlayAnimationReverse(FadeIn);
}