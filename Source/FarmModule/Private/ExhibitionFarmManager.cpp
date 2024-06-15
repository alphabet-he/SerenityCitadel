// Fill out your copyright notice in the Description page of Project Settings.


#include "ExhibitionFarmManager.h"
#include "ExhibitionGrid.h"
#include "Plant.h"
#include "NoiseMapParams.h"
#include "ExhibitionGameMode.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AExhibitionFarmManager::AExhibitionFarmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AExhibitionFarmManager::BeginPlay()
{
	Super::BeginPlay();

	ExhibitionGameMode = Cast<AExhibitionGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ExhibitionGameMode->ExhibitionFarmManager = this;

	TArray<AActor*> grids;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BP_GridActor, grids);

	GridMap.Init(RowSize, ColumnSize, EExhibitionGrid::DIRT);
	GreenValue.Init(RowSize, ColumnSize, 0);
	GridPtrMap.Init(RowSize, ColumnSize, nullptr);
	PlantMap.Init(RowSize, ColumnSize, nullptr);

	for (AActor* grid : grids) {
		AExhibitionGrid* farmingGrid = Cast<AExhibitionGrid>(grid);
		if (farmingGrid) {
			FCoordinate2D coordinate = farmingGrid->coordinate;
			GridMap.SetElement(coordinate.Row, coordinate.Column, farmingGrid->ExhibitionGridType);
			GridPtrMap.SetElement(coordinate.Row, coordinate.Column, farmingGrid);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Error"));
			return;
		}
	}
	
}

TArray2D<float> AExhibitionFarmManager::GeneratePerlinNoiseMap(
	int rowSize, int columnSize, FNoiseMapParams noiseMapParams, float& _seed)
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

			float rowSample = (float)i / rowSize * noiseMapParams.inputRange[1] + noiseMapParams.inputRange[0] + seed;
			float columnSample = (float)j / columnSize * noiseMapParams.inputRange[1] + +noiseMapParams.inputRange[0] + seed;

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

	_seed = seed;
	return noiseMap;
}

TArray<float> AExhibitionFarmManager::GenerateGeometry(int rowSize, int columnSize,
	FNoiseMapParams heightNoiseMapParams, FNoiseMapParams pollutionNoiseMapParams, 
	float waterHeightThreshold, float pollutionThreshold)
{
	float heightSeed = 0;
	float pollutionSeed = 0;
	TArray2D<float> heightMap = GeneratePerlinNoiseMap(rowSize, columnSize, heightNoiseMapParams, heightSeed);
	TArray2D<float> pollutionMap = GeneratePerlinNoiseMap(rowSize, columnSize, pollutionNoiseMapParams, pollutionSeed);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GridMap.Init(rowSize, columnSize, EExhibitionGrid::DIRT);
	GreenValue.Init(rowSize, columnSize, 0);
	GridPtrMap.Init(rowSize, columnSize, nullptr);
	PlantMap.Init(rowSize, columnSize, nullptr);

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++)
		{
			AExhibitionGrid* grid = GetWorld()->SpawnActor<AExhibitionGrid>(BP_GridActor,
				FVector(j * 50, i * 50, heightMap.GetElement(i, j)), FRotator(0, 0, 0), SpawnParameters);
			if (grid) {
				GridPtrMap.SetElement(i, j, grid);

				// is water?
				if (heightMap.GetElement(i, j) < waterHeightThreshold) {
					GridMap.SetElement(i, j, EExhibitionGrid::WATER);
				}
				// is polluted?
				else if (pollutionMap.GetElement(i, j) > pollutionThreshold) {
					GridMap.SetElement(i, j, EExhibitionGrid::POLLUTED);
				}

				grid->coordinate = FCoordinate2D(i, j);
				grid->ExhibitionGridType = GridMap.GetElement(i, j);
				grid->UpdateGrid(GridTextures[static_cast<int>(GridMap.GetElement(i, j))]);
			}
		}
	}

	TArray<float> ret;
	ret.Add(heightSeed);
	ret.Add(pollutionSeed);

	return ret;
}

void AExhibitionFarmManager::ReceiveSignal()
{
}

void AExhibitionFarmManager::OperateGrid(int row, int column)
{
}

void AExhibitionFarmManager::OperatePlant(APlant* plant)
{
}



