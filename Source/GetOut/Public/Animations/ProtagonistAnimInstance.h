// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ProtagonistAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GETOUT_API UProtagonistAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY()
	class AProtagonist* ProtagonistCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Speed;
};
