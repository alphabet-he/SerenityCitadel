// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TArray2D.h"
#include "Coordinate.h"
#include "CommonFarmManager.generated.h"

class AFarmingGrid;
struct FNoiseMapParams;
enum class EGridType : uint8;
class APlant;
enum class EFarmingState : uint8;
class AFarmingRobotCharacter;
class AMyPlayerController;
class UFarmingWidget;
class UMyGameInstanceSubsystem;

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
	TArray2D<FVector> GridLocationMap;

	AFarmingRobotCharacter* PlayerCharacter;
	AMyPlayerController* PlayerController;

	// the location, the max percentage to evaporate
	TMap<FCoordinate2D, float> WaterEvaporateGrids;

	TArray<FCoordinate2D> SeededGrids;

	UFarmingWidget* FarmingWidget;

	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

	FVector LastAnalysisPlayerLocation;
	FCoordinate2D LastAnalysisGridCoordinate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFarmingWidget> FarmingWidgetClass;

	UPROPERTY(EditAnywhere)
	float PlantGrowthMoistureThreshold = 0.5f;

	UPROPERTY(EditAnywhere)
	float PlantGrowthPollutionThreshold = 0.35f;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> GridTextures;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* PollutedMaterial;

	UPROPERTY(EditAnywhere)
	UStaticMesh* DiggedGridMesh;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SeededGridMesh;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APlant>> NaturalPlants;

	UPROPERTY(EditAnywhere)
	TArray<EGridType> CanDigTypes;

	UPROPERTY(EditAnywhere)
	float SandMoistureThreshold;
	UPROPERTY(EditAnywhere)
	float WaterMoistureThreshold;
	UPROPERTY(EditAnywhere)
	float WaterHeightThreshold;
	UPROPERTY(EditAnywhere)
	float PollutionThreshold;

	UPROPERTY(EditAnywhere)
	float WaterEvaporatePercent;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAllGrids();

	UFUNCTION(BlueprintCallable)
	void UpdateGridsFromTypes(TArray<EGridType> types);

	UFUNCTION(BlueprintCallable)
	inline void ChangeGridType(FCoordinate2D gridCoordinate, EGridType newType) 
	{
		if (GridTypeMap.IsEmpty()) return;
		if (gridCoordinate.Row < 0 || gridCoordinate.Row >= GridTypeMap.GetRow()
			|| gridCoordinate.Column < 0 || gridCoordinate.Column >= GridTypeMap.GetRow())
			return;
		GridTypeMap.SetElement(gridCoordinate.Row, gridCoordinate.Column, static_cast<int>(newType));
	};

	UFUNCTION(BlueprintCallable)
	void UpdateGridBasedOnTypeMap(FCoordinate2D gridCoordinate);

	UFUNCTION(BlueprintCallable)
	void CheckAndUpdateGrid(FCoordinate2D gridCoordinate);

	UFUNCTION(BlueprintCallable)
	void CheckAndUpdatePollution(FCoordinate2D gridCoordinate);

	UFUNCTION(BlueprintCallable)
	virtual bool Analyze();

	UFUNCTION(BlueprintCallable)
	virtual bool Operate(EFarmingState action);

	UFUNCTION(BlueprintCallable)
	AFarmingGrid* FindGridUnderPlayer();

	UFUNCTION(BlueprintCallable)
	FCoordinate2D FindGridAtLocation(FVector location);

	UFUNCTION(BlueprintCallable)
	virtual bool OperateOnGrid(FCoordinate2D gridCoordinate, EFarmingState action);

	virtual bool Dig(FCoordinate2D gridCoordinate);
	virtual bool Water(FCoordinate2D gridCoordinate);
	virtual bool Decontaminate(FCoordinate2D gridCoordinate);
	virtual bool Seed(FCoordinate2D gridCoordinate);

	void UpdateState(FString stateName);

protected:
	TArray2D<float> GeneratePerlinNoiseMap(int rowSize, int columnSize, FNoiseMapParams noiseMapParams);

	void SpawnRandomPlant(FCoordinate2D loc);

	void UpdateFarmingWidgetSuggestions(FCoordinate2D coordinate);

};
