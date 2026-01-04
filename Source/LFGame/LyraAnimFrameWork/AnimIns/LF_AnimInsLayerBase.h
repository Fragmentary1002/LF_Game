// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LF_AnimInsLayerBase.generated.h"

/**
 * 
 */
UCLASS()
class LFGAME_API ULF_AnimInsLayerBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintable,,meta=(BlueprintThreadSafe))
	ULF_AnimInsBase*  GetMainABPThreadSafe();

	
};
