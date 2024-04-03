// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StringArray.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStringArray
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> StringArray;

};
