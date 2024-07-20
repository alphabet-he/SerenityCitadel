// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TArray2D.h"
#include "ExhibitionFarmManager.generated.h"

class AExhibitionGrid;
class APlant;
struct FNoiseMapParams;
class AExhibitionGameMode;

UENUM(BlueprintType)
enum class EExhibitionGrid : uint8 {
	POLLUTED = 0 UMETA(ToolTip = "Polluted"),
	DIRT = 1 UMETA(ToolTip = "Dirt"),
	GRASS = 2 UMETA(ToolTip = "Grass"),
	WATER = 3 UMETA(ToolTip = "Water")
};

UCLASS()
class AExhibitionFarmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExhibitionFarmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray2D<float> GeneratePerlinNoiseMap(
		int rowSize, int columnSize, FNoiseMapParams noiseMapParams, float& _seed);

	UFUNCTION(BlueprintCallable)
	TArray<float> GenerateGeometry(
		int rowSize, int columnSize, 
		FNoiseMapParams heightNoiseMapParams, FNoiseMapParams pollutionNoiseMapParams,
		float waterHeightThreshold, float pollutionThreshold
	);



	UFUNCTION(BlueprintCallable)
	AExhibitionGrid* GetGrid(int rowInd, int colInd) {
		return GridPtrMap.GetElement(rowInd, colInd);
	};

	// bExecute: do change or only check availability
	UFUNCTION(BlueprintCallable)
	bool Operate(int rowInd, int colInd, bool bExecute);

	// Operate 3*3 range grid
	UFUNCTION(BlueprintCallable)
	bool OperateRange(int rowInd, int colInd);


	UFUNCTION(BlueprintCallable)
	bool Save();

	UFUNCTION(BlueprintCallable)
	bool Load();

	UFUNCTION(BlueprintCallable)
	TArray<bool> Decode(const uint8 b);

	UFUNCTION(BlueprintCallable)
	uint8 Encode (TArray<bool> boolArray);

	UFUNCTION(BlueprintCallable)
	UMaterialInstance* GetTexture(EExhibitionGrid type) {
		return GridTextures[static_cast<int>(type)];
	}

protected:
	TArray2D<float> GreenValue;
	TArray2D<AExhibitionGrid*> GridPtrMap;
	AExhibitionGameMode* ExhibitionGameMode;

	UPROPERTY(EditAnywhere)
	TArray<AExhibitionGrid*> TempGridPtrArray;

public:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APlant>> PossiblePlants;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AExhibitionGrid> BP_GridActor;

	/** Polluted, Dirt, Grass, Water */
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> GridTextures;

	UPROPERTY(EditAnywhere)
	int RowSize;

	UPROPERTY(EditAnywhere)
	int ColumnSize;


	TArray2D<AExhibitionGrid*> GetGridPtrMap() {
		return GridPtrMap;
	}
};
