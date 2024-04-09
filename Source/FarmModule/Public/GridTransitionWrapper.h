// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <FarmModuleEnums.h>
#include "Containers/Map.h"
#include "GridTransitionWrapper.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FGridTransitionWrapper
{
    GENERATED_BODY()

    FGridTransitionWrapper() {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EGridType _GridType;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 OperationNum;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<GridOperation, EGridType> OperationMapping;


};
