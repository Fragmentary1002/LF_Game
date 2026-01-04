// Fill out your copyright notice in the Description page of Project Settings.


#include "LF_AnimInsLayerBase.h"
#include "LF_AnimInsBase.h"

ULF_AnimInsBase* ULF_AnimInsLayerBase::GetMainABPThreadSafe()
{
    if (UAnimInstance* AnimIns = GetOwningComponent() ? GetOwningComponent()->GetAnimInstance() : nullptr)
    {
        return Cast<ULF_AnimInsBase>(AnimIns);
    }
    return nullptr;
}