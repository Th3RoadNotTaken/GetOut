// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InteractWidget.h"
#include "Components/TextBlock.h"

void UInteractWidget::UpdateInteractionText(FString Text)
{
	InteractionText->SetText(FText::FromString(Text));
}