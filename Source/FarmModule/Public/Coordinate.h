// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coordinate.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCoordinate2D
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Row;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Column;

    FCoordinate2D() {
    };

    FCoordinate2D(int32 row, int32 column)
    {
        Row = row;
        Column = column;
    };

};
