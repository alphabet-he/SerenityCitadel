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

    // Equality operator overload
    bool operator==(const FCoordinate2D& Other) const
    {
        return Row == Other.Row && Column == Other.Column;
    }

    // Overload GetTypeHash for FCoordinate2D
    friend FORCEINLINE uint32 GetTypeHash(const FCoordinate2D& Coordinate)
    {
        // Combine the hashes of the individual properties
        uint32 HashX = ::GetTypeHash(Coordinate.Row);
        uint32 HashY = ::GetTypeHash(Coordinate.Column);

        return HashCombine(HashX, HashY);
    }

};
