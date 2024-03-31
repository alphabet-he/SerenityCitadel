// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TArray2D.h"
#include "Coordinate.h"
#include "CommonFarmManager.generated.h"

class AFarmingGrid;
struct FNoiseMapParams;
enum class GridType : uint8;
class APlant;

UCLASS()
class FARMMODULE_API ACommonFarmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommonFarmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	TArray2D<int> GridTypeMap;
	TArray2D<AFarmingGrid*> GridPtrMap;
	TMap<FVector, AFarmingGrid*> LocationGridMap;

public:
	UPROPERTY(EditAnywhere)
	TArray<UMaterial*> GridTextures;

	UPROPERTY(EditAnywhere)
	UMaterial* PollutedMaterial;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APlant>> NaturalPlants;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAllGrids();

	UFUNCTION(BlueprintCallable)
	void UpdateGridsFromTypes(TArray<GridType> types);

	UFUNCTION(BlueprintCallable)
	inline void ChangeGridType(FCoordinate2D gridCoordinate, GridType newType) 
	{
		if (GridTypeMap.IsEmpty()) return;
		if (gridCoordinate.Row < 0 || gridCoordinate.Row >= GridTypeMap.GetRow()
			|| gridCoordinate.Column < 0 || gridCoordinate.Column >= GridTypeMap.GetRow())
			return;
		GridTypeMap.SetElement(gridCoordinate.Row, gridCoordinate.Column, static_cast<int>(newType));
	};

	UFUNCTION(BlueprintCallable)
	void UpdateGrid(FCoordinate2D gridCoordinate);

	UFUNCTION(BlueprintCallable)
	AFarmingGrid* FindGridUnderPlayer();

	UFUNCTION(BlueprintCallable)
	AFarmingGrid* FindGridAtLocation();

	TArray2D<float> GeneratePerlinNoiseMap(int rowSize, int columnSize, FNoiseMapParams noiseMapParams);

	void SpawnRandomPlant(FCoordinate2D loc);
};
