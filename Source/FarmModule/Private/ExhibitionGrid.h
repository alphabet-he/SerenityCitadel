// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmingGrid.h"
#include "ExhibitionFarmManager.h"
#include "ExhibitionGrid.generated.h"

/**
 * 
 */
UCLASS()
class AExhibitionGrid : public AFarmingGrid
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EExhibitionGrid ExhibitionGridType;

	UFUNCTION(BlueprintCallable)
	EExhibitionGrid GetType() {
		return ExhibitionGridType;
	}
	
};
