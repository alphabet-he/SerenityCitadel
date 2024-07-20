// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmingGrid.h"
#include "ExhibitionFarmManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ExhibitionGrid.generated.h"

/**
 * 
 */
UCLASS()
class AExhibitionGrid : public AFarmingGrid
{
	GENERATED_BODY()

public:
	AExhibitionGrid();

	void ActivateEffect() {
		NiagaraEffect->Activate();
	};

	UPROPERTY(EditAnywhere)
	EExhibitionGrid ExhibitionGridType;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* NiagaraEffect;

	UFUNCTION(BlueprintCallable)
	EExhibitionGrid GetType() {
		return ExhibitionGridType;
	}

	UFUNCTION(BlueprintCallable)
	FCoordinate2D GetCoordinate() {
		return coordinate;
	}
	
};
