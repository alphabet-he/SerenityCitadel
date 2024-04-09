// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TArray2D.h"
#include "Coordinate.h"
#include "NoiseMapParams.h"
#include <GridTransitionWrapper.h>
#include "FarmingSubsystem.generated.h"

/**
 * 
 */

class AFarmingGrid;
class UOperatingWidget;
enum class EGridType: uint8;

UCLASS()
class FARMMODULE_API UFarmingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	const static int GridUnitLength = 100; // length of the grid of scale 1

	UPROPERTY(BlueprintReadWrite)
	TArray<UMaterial*> GridTextures;

	UPROPERTY(BlueprintReadWrite)
	int GridScale = 1;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AActor> BP_GridActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<EGridType, FGridTransitionWrapper> GridTransitionMapping;

private:
	TArray2D<int> GridMap;
	TArray2D<AFarmingGrid*> GridPtrs;
	UOperatingWidget* OperatingWidget;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnGrid(const FVector p1, const FVector p2, 
		FNoiseMapParams heightMapParams, FNoiseMapParams moistureMapParams, FNoiseMapParams temperatureMapParams,
		float sandMoistureThreshold, float sandTemperatureThreshold,
		float waterMoistureThreshold, float waterHeightThreshold, 
		float rockPercent);

	UFUNCTION(BlueprintCallable)
	void SpawnGridRandom(const FVector p1, const FVector p2);
	
	FORCEINLINE TArray2D<int> GetGridMap() 
	{
		return GridMap;
	};

	UFUNCTION(BlueprintCallable) void ChangeGrid(FCoordinate2D gridCoordinate, EGridType newType);

private:
	FORCEINLINE float GetDist(FCoordinate2D p1, FCoordinate2D p2) const {
		return sqrt((p1.Row - p2.Row) ^ 2 + (p1.Column - p2.Column) ^ 2);
	};

	FORCEINLINE float GetValue(float exptValue, int attemptNum, float IncProb, float DecProb) const {
		FRandomStream Stream(FMath::Rand());
		int val = exptValue;
		for (int i = 0; i < attemptNum; i++) {
			float r = FMath::FRandRange(0.0f, 1.0f);
			if (r < IncProb) val++;
			if (r > (1 - DecProb)) val--;
		}
		return val;
	};

	void GenerateSandArea(
		int exptRadius, int radiusAttemptNum, float radiusIncProb, float radiusDecProb,
		float boundaryIncProb, float boundaryDecProb
	);	
	void QueueSurrGridOfType(int x, int y, EGridType type, TQueue<FCoordinate2D>& queue);
	void ModifyEdgePoint(int x, int y, float boundaryIncProb, float boundaryDecProb);
	void GenerateRiver(
		int riverExpandMargin, int lakeExpandMargin,
		float exptLength, int lengthAttemptNum, float lengthIncProb, float lengthDecProb, float lengthDevRange,
		int randomPairAttempNum,
		float wanderProb,
		int exptMaxWidth, int maxWidthAttemptNum, float maxWidthIncProb, float maxWidthDecProb,
		int exptMinWidth, int minWidthAttemptNum, float minWidthIncProb, float minWidthDecProb,
		float lakeProb,
		int exptLakeRadius, int lakeRadiusAttemptNum, float lakeRadiusIncProb, float lakeRadiusDecProb
	);
	
	TArray<FVector> GenerateWanderingLine(const FVector& Start, const FVector& End, int32 NumPoints, float NoiseScale, float MaxOffset);

	void UpdateAllGrids();
	void UpdateGridsFromTypes(TArray<EGridType> types);

	TArray2D<float> GeneratePerlinNoiseMap(int rowSize, int columnSize, FNoiseMapParams noiseMapParams);

	void SaveArrayToCSV(const TArray<int32>& MyArray, const FString& FilePath);


};
