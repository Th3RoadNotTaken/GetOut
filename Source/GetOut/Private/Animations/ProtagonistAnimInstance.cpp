// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ProtagonistAnimInstance.h"
#include "Characters/Protagonist.h"

void UProtagonistAnimInstance::NativeInitializeAnimation()
{
	ProtagonistCharacter = Cast<AProtagonist>(TryGetPawnOwner());
}

void UProtagonistAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(!ProtagonistCharacter)
		ProtagonistCharacter = Cast<AProtagonist>(TryGetPawnOwner());
	if (!ProtagonistCharacter)
		return;

	Speed = ProtagonistCharacter->GetVelocity().Size();
}
