// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFarmManager.h"
#include "FarmingGrid.h"
#include "NoiseMapParams.h"
#include "FarmModuleEnums.h"
#include "Plant.h"
#include <Components/ArrowComponent.h>

// Sets default values
ACommonFarmManager::ACommonFarmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACommonFarmManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACommonFarmManager::UpdateAllGrids()
{
	if (GridTypeMap.IsEmpty()) return;
	for (int i = 0; i < GridPtrMap.GetRow(); i++) {
		for (int j = 0; j < GridPtrMap.GetColumn(); j++) {
			UpdateGrid(FCoordinate2D{ i, j });
		}
	}
}

void ACommonFarmManager::UpdateGridsFromTypes(TArray<GridType> types)
{
	if (GridTypeMap.IsEmpty()) return;

	TArray<int> typeInts;
	for (GridType type : types) {
		typeInts.AddUnique(static_cast<int>(type));
	}

	// iterate through the grid map
	for (int i = 0; i < GridTypeMap.GetRow(); i++) {
		for (int j = 0; j < GridTypeMap.GetColumn(); j++) {
			if (typeInts.Contains(GridTypeMap.GetElement(i, j))) {
				continue;
			}
			else {
				UpdateGrid(FCoordinate2D{ i, j });
			}
		}
	}
}

void ACommonFarmManager::UpdateGrid(FCoordinate2D gridCoordinate)
{
	if (GridTypeMap.IsEmpty()) return;

	int type = GridTypeMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);
	GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->setGridType(
		static_cast<GridType>(type));
	if (GridTextures[type]) {
		GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->UpdateGrid(GridTextures[type]);
	}
	else {
		GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->UpdateGrid();
	}

}

AFarmingGrid* ACommonFarmManager::FindGridUnderPlayer()
{
	return nullptr;
}

AFarmingGrid* ACommonFarmManager::FindGridAtLocation()
{
	return nullptr;
}

TArray2D<float> ACommonFarmManager::GeneratePerlinNoiseMap(int rowSize, int columnSize, FNoiseMapParams noiseMapParams)
{
	if (noiseMapParams.inputRange.Num() != 2) {
		UE_LOG(LogTemp, Warning, TEXT("Noise map params wrong! Expected 2 input range - received %i"), noiseMapParams.inputRange.Num());
		TArray2D<float> noiseMap;
		return noiseMap;
	}

	TArray2D<float> noiseMap;
	noiseMap.Init(rowSize, columnSize, 0);

	// determine seed
	float seed = 0;
	if (noiseMapParams.bUseSeed) {
		seed = noiseMapParams.seed;
	}
	else {
		FRandomStream Stream(FMath::Rand());
		seed = FMath::Rand();
	}

	// determine multiplier
	float multiplier = 1;
	if (noiseMapParams.bMultiplier) {
		multiplier = noiseMapParams.multiplier;
	}

	// generate noise values
	float maxVal = INT_MIN;
	float minVal = INT_MAX;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < columnSize; j++) {

			float rowSample = (float)i / rowSize * noiseMapParams.inputRange[0] + seed;
			float columnSample = (float)j / columnSize * noiseMapParams.inputRange[1] + seed;

			float value = FMath::PerlinNoise2D(FVector2D{ columnSample, rowSample }) * multiplier;
			if (value > maxVal) maxVal = value;
			if (value < minVal) minVal = value;
			noiseMap.SetElement(i, j, value);
		}
	}

	// scale noise map
	if (noiseMapParams.bScale && maxVal != minVal) {
		for (int i = 0; i < rowSize; i++) {
			for (int j = 0; j < columnSize; j++) {
				float scaledVal = noiseMap.GetElement(i, j);
				scaledVal = (scaledVal - minVal) / (maxVal - minVal) * (noiseMapParams.max - noiseMapParams.min) + noiseMapParams.min;
				noiseMap.SetElement(i, j, scaledVal);
			}
		}
	}

	return noiseMap;
}

void ACommonFarmManager::SpawnRandomPlant(FCoordinate2D loc)
{
	FRandomStream Stream(FMath::Rand());
	int rndInd = FMath::RandRange(0, NaturalPlants.Num() - 1);
	AFarmingGrid* grid = GridPtrMap.GetElement(loc.Row, loc.Column);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APlant* spawnedPlant = GetWorld()->SpawnActor<APlant>(NaturalPlants[rndInd],
		grid->PlantMark->GetComponentLocation(), grid->PlantMark->GetComponentRotation(),
		SpawnParameters);

	if (spawnedPlant) {
		grid->setPlant(spawnedPlant);
	}
}

