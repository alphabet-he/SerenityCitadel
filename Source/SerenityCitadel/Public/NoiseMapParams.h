// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoiseMapParams.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNoiseMapParams {

	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<float> inputRange; // row-x, column-y

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseSeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float seed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float max;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float min;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float multiplier;
};
