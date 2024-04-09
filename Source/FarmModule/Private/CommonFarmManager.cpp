// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFarmManager.h"
#include "FarmingGrid.h"
#include "NoiseMapParams.h"
#include "FarmModuleEnums.h"
#include "Plant.h"
#include <Components/ArrowComponent.h>
#include "FarmingRobotCharacter.h"
#include "MyPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetComponent.h>


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

	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = Cast<AFarmingRobotCharacter>(PlayerController->GetPlayerCharacter());
	check(PlayerCharacter);
	
}

void ACommonFarmManager::UpdateAllGrids()
{
	if (GridTypeMap.IsEmpty()) return;
	for (int i = 0; i < GridPtrMap.GetRow(); i++) {
		for (int j = 0; j < GridPtrMap.GetColumn(); j++) {
			UpdateGridBasedOnTypeMap(FCoordinate2D{ i, j });
		}
	}
}

void ACommonFarmManager::UpdateGridsFromTypes(TArray<EGridType> types)
{
	if (GridTypeMap.IsEmpty()) return;

	TArray<int> typeInts;
	for (EGridType type : types) {
		typeInts.AddUnique(static_cast<int>(type));
	}

	// iterate through the grid map
	for (int i = 0; i < GridTypeMap.GetRow(); i++) {
		for (int j = 0; j < GridTypeMap.GetColumn(); j++) {
			if (typeInts.Contains(GridTypeMap.GetElement(i, j))) {
				continue;
			}
			else {
				UpdateGridBasedOnTypeMap(FCoordinate2D{ i, j });
			}
		}
	}
}

void ACommonFarmManager::UpdateGridBasedOnTypeMap(FCoordinate2D gridCoordinate)
{
	if (GridTypeMap.IsEmpty()) return;

	int type = GridTypeMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);
	GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->setGridType(
		static_cast<EGridType>(type));
	if (GridTextures[type]) {
		GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->UpdateGrid(GridTextures[type]);
	}
	else {
		GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)->UpdateGrid();
	}

}

void ACommonFarmManager::CheckAndUpdateGrid(FCoordinate2D gridCoordinate) {
	
	AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);

	// check sand
	if (grid->MoisturePercentage < SandMoistureThreshold) {
		GridTypeMap.SetElement(gridCoordinate.Row, gridCoordinate.Column,
			static_cast<int>(EGridType::SAND));
		UpdateGridBasedOnTypeMap(gridCoordinate);
	}

	// check water
	if (grid->MoisturePercentage > WaterMoistureThreshold
		&& grid->Height < WaterHeightThreshold) {
		GridTypeMap.SetElement(gridCoordinate.Row, gridCoordinate.Column,
			static_cast<int>(EGridType::WATER));
		UpdateGridBasedOnTypeMap(gridCoordinate);
	}

}

void ACommonFarmManager::CheckAndUpdatePollution(FCoordinate2D gridCoordinate) 
{
	AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);
	if (grid->PollutionPercent > PollutionThreshold) {
		grid->bPolluted = true;
		grid->UpdatePolluted(PollutedMaterial);
	}

	else {
		grid->bPolluted = false;
		grid->ClearPolluted();
	}
}

bool ACommonFarmManager::Operate(EFarmingState action)
{
	FCoordinate2D coordinate = FindGridAtLocation(PlayerCharacter->TargetWidget->GetComponentLocation());
	AFarmingGrid* grid = GridPtrMap.GetElement(coordinate.Row, coordinate.Column);
	//grid->GridMesh->SetMaterial(0, nullptr);

	if (action == EFarmingState::DIGGING) { return Dig(coordinate); }
	if (action == EFarmingState::WATERING) { return Water(coordinate); }
	if (action == EFarmingState::DECONTAMINATING) { return Decontaminate(coordinate); }
	if (action == EFarmingState::SEEDING) { return Seed(coordinate); }
	return false;
}

AFarmingGrid* ACommonFarmManager::FindGridUnderPlayer()
{
	return nullptr;
}

FCoordinate2D ACommonFarmManager::FindGridAtLocation(FVector location)
{
	int RowNum = GridTypeMap.GetRow();
	int ColNum = GridTypeMap.GetColumn();

	int desiredRow = -1;
	int desiredCol = -1;

	// find column
	float currDist = INT_MAX;
	for (int i = 0; i < ColNum; i++) {
		float dist = FVector::Dist(location, GridLocationMap.GetElement(0, i));
		if (dist <= currDist) {
			currDist = dist;
			desiredCol = i;
		}
	}

	// find row
	currDist = INT_MAX;
	for (int i = 0; i < RowNum; i++) {
		float dist = FVector::Dist(location, GridLocationMap.GetElement(i, 0));
		if (dist <= currDist) {
			currDist = dist;
			desiredRow = i;
		}
	}

	return FCoordinate2D{ desiredRow, desiredCol };
}

bool ACommonFarmManager::OperateOnGrid(FCoordinate2D gridCoordinate, EFarmingState action)
{
	
	return false;
}

bool ACommonFarmManager::Dig(FCoordinate2D gridCoordinate)
{
	if (CanDigTypes.Contains(static_cast<EGridType>(GridTypeMap.GetElement(gridCoordinate.Row, gridCoordinate.Column)))) {
		AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);
		// no plant on it
		if (!grid->EntityAbove) {
			grid->bDigged = true;
			grid->GridMesh->SetStaticMesh(DiggedGridMesh);
			return true;
		}
	}
	return false;
}

bool ACommonFarmManager::Water(FCoordinate2D gridCoordinate)
{
	AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);

	float intendedMoisture = PlayerCharacter->WaterAddMoisture + grid->MoisturePercentage;

	if (intendedMoisture > 1) {
		WaterEvaporateGrids.Add(gridCoordinate, 1 - grid->MoisturePercentage);
		grid->MoisturePercentage = 1;
	}
	else {
		WaterEvaporateGrids.Add(gridCoordinate, PlayerCharacter->WaterAddMoisture);
		grid->MoisturePercentage += PlayerCharacter->WaterAddMoisture;
	}

	CheckAndUpdateGrid(gridCoordinate);

	return true;
}

bool ACommonFarmManager::Decontaminate(FCoordinate2D gridCoordinate)
{
	AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);

	grid->PollutionPercent = fmin(0, grid->PollutionPercent - PlayerCharacter->DecontaminateMinusPollution);

	CheckAndUpdatePollution(gridCoordinate);

	return true;
}

bool ACommonFarmManager::Seed(FCoordinate2D gridCoordinate)
{
	if (PlayerCharacter->SeedPackage[PlayerCharacter->GetHoldingSeed()] <= 0) {
		return false;
	}

	AFarmingGrid* grid = GridPtrMap.GetElement(gridCoordinate.Row, gridCoordinate.Column);
	if (!grid->bDigged) {
		return false;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APlant* spawnedPlant = GetWorld()->SpawnActor<APlant>(PlayerCharacter->GetHoldingSeed(),
		grid->PlantMark->GetComponentLocation(), grid->PlantMark->GetComponentRotation(),
		SpawnParameters);

	if (spawnedPlant) {
		grid->EntityAbove = spawnedPlant;
		grid->GridMesh->SetStaticMesh(SeededGridMesh);
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Seed failed"));
		return false;
	}
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
		grid->EntityAbove = spawnedPlant;
	}
}

