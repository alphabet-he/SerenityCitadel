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

	GreenValue.Init(RowSize, ColumnSize, 0);
	GridPtrMap.Init(RowSize, ColumnSize, nullptr);

	int tempArrInd = 0;
	for (int i = 0; i < RowSize; i++) {
		for (int j = 0; j < ColumnSize; j++) {
			GridPtrMap.SetElement(i, j, TempGridPtrArray[tempArrInd]);
			tempArrInd++;
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

	TempGridPtrArray.Empty();

	TArray2D<float> heightMap = GeneratePerlinNoiseMap(rowSize, columnSize, heightNoiseMapParams, heightSeed);
	TArray2D<float> pollutionMap = GeneratePerlinNoiseMap(rowSize, columnSize, pollutionNoiseMapParams, pollutionSeed);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GreenValue.Init(rowSize, columnSize, 0);
	GridPtrMap.Init(rowSize, columnSize, nullptr);

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++)
		{
			AExhibitionGrid* grid = GetWorld()->SpawnActor<AExhibitionGrid>(BP_GridActor,
				FVector(j * 50, i * 50, heightMap.GetElement(i, j)), FRotator(0, 0, 0), SpawnParameters);
			if (grid) {
				GridPtrMap.SetElement(i, j, grid);
				TempGridPtrArray.Add(grid);

				grid->ExhibitionGridType = EExhibitionGrid::DIRT; // Default type is dirt

				// is water?
				if (heightMap.GetElement(i, j) < waterHeightThreshold) {
					grid->ExhibitionGridType = EExhibitionGrid::WATER;
				}
				// is polluted?
				else if (pollutionMap.GetElement(i, j) > pollutionThreshold) {
					grid->ExhibitionGridType =  EExhibitionGrid::POLLUTED;
				}

				grid->coordinate = FCoordinate2D(i, j);
				grid->UpdateGrid(GridTextures[static_cast<int>(grid->ExhibitionGridType)]);
			}
		}
	}

	TArray<float> ret;
	ret.Add(heightSeed);
	ret.Add(pollutionSeed);

	return ret;
}


bool AExhibitionFarmManager::Operate(int rowInd, int colInd, bool bExecute)
{
	AExhibitionGrid* grid = GridPtrMap.GetElement(rowInd, colInd);

	if (grid->ExhibitionGridType == EExhibitionGrid::WATER) {
		return false;
	}
	if (grid->ExhibitionGridType == EExhibitionGrid::POLLUTED ||
		grid->ExhibitionGridType == EExhibitionGrid::DIRT) {

		if (bExecute) {
			int currTypeInt = static_cast<int>(grid->ExhibitionGridType);
			currTypeInt++;
			grid->ExhibitionGridType = static_cast<EExhibitionGrid>(currTypeInt);
			grid->UpdateGrid(GridTextures[currTypeInt]);
		}

		return true;
	}
	if (grid->ExhibitionGridType == EExhibitionGrid::GRASS) {
		if (grid->EntityAbove && 
			Cast<APlant>(grid->EntityAbove)) {
			// has plant
			APlant* plant = Cast<APlant>(grid->EntityAbove);
			return plant->Grow(bExecute);
		}
		else {
			// no plant yet
			if (bExecute) {
				FRandomStream Stream(FMath::Rand());
				int type = FMath::RandRange(0, PossiblePlants.Num() - 1);
				TSubclassOf<APlant> plantType = PossiblePlants[type];
				if (grid->PutEntityAbove(plantType)) {
					APlant* plant = Cast<APlant>(grid->EntityAbove);
					if (plant) {
						plant->PlantType = type;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}

			return true;
			
		}
	}

	return false;
}

bool AExhibitionFarmManager::OperateRange(int rowInd, int colInd)
{
	if (Operate(rowInd, colInd, true)) {
		for (int i = rowInd - 1; i <= rowInd + 1; i++) {
			for (int j = colInd - 1; j <= colInd + 1; j++) {
				if (i == rowInd && j == colInd) continue;
				if (i < 0 || i >= RowSize ||
					j < 0 || j >= ColumnSize) continue;
				AExhibitionGrid* grid = GridPtrMap.GetElement(i, j);
				if (grid->ExhibitionGridType != EExhibitionGrid::GRASS) {
					Operate(i, j, true);
				}
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool AExhibitionFarmManager::Save()
{
	FString dirPath = FPaths::ProjectDir();
	FString gridTypePath = dirPath + "\\grid_type_save.txt";
	FString plantTypePath = dirPath + "\\plant_type_save.txt";
	FString plantStatePath = dirPath + "\\plant_state_save.txt";

	FString gridTypeString = "";
	FString plantTypeString = "";
	FString plantStateString = "";

	for (int i = 0; i < RowSize; i++) {
		for (int j = 0; j < ColumnSize; j++) {
			AExhibitionGrid* grid = GridPtrMap.GetElement(i, j);

			// grid type
			gridTypeString += FString::Printf(TEXT("%i,"),
				static_cast<int>(grid->ExhibitionGridType));

			// plant type & state
			if (grid->EntityAbove) {
				APlant* plant = Cast<APlant>(grid->EntityAbove);
				if (plant) {
					plantTypeString += FString::Printf(TEXT("%i,"), plant->PlantType);
					plantStateString += FString::Printf(TEXT("%i,"), plant->CurrentGrowthState);

				}
				else {
					plantTypeString += FString::Printf(TEXT("%i,"), -1);
					plantStateString += FString::Printf(TEXT("%i,"), -1);
				}
			}
			else {
				plantTypeString += FString::Printf(TEXT("%i,"),-1);
				plantStateString += FString::Printf(TEXT("%i,"), -1);
			}

		}
	}


	return (FFileHelper::SaveStringToFile(gridTypeString, *gridTypePath)
		&& FFileHelper::SaveStringToFile(plantTypeString, *plantTypePath)
		&& FFileHelper::SaveStringToFile(plantStateString, *plantStatePath));
}

bool AExhibitionFarmManager::Load()
{
	FString dirPath = FPaths::ProjectDir();
	FString gridTypePath = dirPath + "\\grid_type_save.txt";
	FString plantTypePath = dirPath + "\\plant_type_save.txt";
	FString plantStatePath = dirPath + "\\plant_state_save.txt";

	FString gridTypeString = "";
	FString plantTypeString = "";
	FString plantStateString = "";

	
	FFileHelper::LoadFileToString(gridTypeString, *gridTypePath);
	FFileHelper::LoadFileToString(plantTypeString, *plantTypePath);
	FFileHelper::LoadFileToString(plantStateString, *plantStatePath);

	TArray<FString> gridTypeStrings;
	TArray<FString> plantTypeStrings;
	TArray<FString> plantStateStrings;

	gridTypeString.ParseIntoArray(gridTypeStrings, TEXT(","), true);
	plantTypeString.ParseIntoArray(plantTypeStrings, TEXT(","), true);
	plantStateString.ParseIntoArray(plantStateStrings, TEXT(","), true);

	if (gridTypeStrings.Num() != RowSize * ColumnSize ||
		plantTypeStrings.Num() != RowSize * ColumnSize ||
		plantStateStrings.Num() != RowSize * ColumnSize) {
		return false;
	}

	int ind = 0;
	for (int i = 0; i < RowSize; i++) {
		for (int j = 0; j < ColumnSize; j++) {
			AExhibitionGrid* grid = GridPtrMap.GetElement(i, j);

			// grid type
			int gridTypeInt = FCString::Atoi(*(gridTypeStrings[ind].TrimStartAndEnd()));
			EExhibitionGrid gridType = static_cast<EExhibitionGrid>(gridTypeInt);
			if (grid->ExhibitionGridType != gridType) {
				grid->ExhibitionGridType = gridType;
				grid->UpdateGrid(GridTextures[gridTypeInt]);
			}

			// plant
			int plantTypeInt = FCString::Atoi(*(plantTypeStrings[ind].TrimStartAndEnd()));
			if (plantTypeInt != -1) {
				if (grid->PutEntityAbove(PossiblePlants[plantTypeInt])) {
					
					APlant* plant = Cast<APlant>(grid->EntityAbove);
					if (plant) {
						plant->PlantType = plantTypeInt;
						int plantStateInt = FCString::Atoi(*(plantStateStrings[ind].TrimStartAndEnd()));
						plant->GrowToState(plantStateInt);
					}
				}
			
			}

			ind++;
		}
	}
	return true;
}

TArray<bool> AExhibitionFarmManager::Decode(const uint8 b)
{
	TArray<bool> ret;
	ret.Init(false, 4);
	if (b & 1) ret[0] = true;
	if (b & 2) ret[1] = true;
	if (b & 4) ret[2] = true;
	if (b & 8) ret[3] = true;
	return ret;
}

uint8 AExhibitionFarmManager::Encode(TArray<bool> boolArray)
{
	uint8 byte = 0;
	for (int i = 0; i < 4; i++) {
		if (boolArray[i]) byte |= (1 << i);
	}
	return byte;
}


