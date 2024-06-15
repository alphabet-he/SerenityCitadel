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
	void ReceiveSignal();

	void OperateGrid(int row, int column);

	void OperatePlant(APlant* plant);

protected:
	TArray2D<EExhibitionGrid> GridMap;
	TArray2D<float> GreenValue;
	TArray2D<AExhibitionGrid*> GridPtrMap;
	TArray2D<APlant*> PlantMap;
	AExhibitionGameMode* ExhibitionGameMode;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AExhibitionGrid> BP_GridActor;

	/** Polluted, Dirt, Grass, Water */
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> GridTextures;

	UPROPERTY(EditAnywhere)
	int RowSize;

	UPROPERTY(EditAnywhere)
	int ColumnSize;

	TArray2D<EExhibitionGrid> GetGridMap() {
		return GridMap;
	}

	TArray2D<AExhibitionGrid*> GetGridPtrMap() {
		return GridPtrMap;
	}
};
