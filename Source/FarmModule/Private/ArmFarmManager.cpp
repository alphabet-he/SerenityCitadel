// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmFarmManager.h"
#include "FarmingGrid.h"

// Sets default values
AArmFarmManager::AArmFarmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AArmFarmManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnArmGrids();
}

void AArmFarmManager::GenerateGeometry(FNoiseMapParams HeightMapParams, 
	FNoiseMapParams MoistureMapParams, FNoiseMapParams PollutionMapParams, 
	float SandMoistureThreshold, 
	float WaterMoistureThreshold, float WaterHeightThreshold, 
	float PollutionThreshold, 
	float PlantGrowthProb)
{
	TArray2D<float> heightMap = GeneratePerlinNoiseMap(CycleNum, GridCountPerCycle, HeightMapParams);
	TArray2D<float> moistureMap = GeneratePerlinNoiseMap(CycleNum, GridCountPerCycle, HeightMapParams);
	TArray2D<float> pollutionMap = GeneratePerlinNoiseMap(CycleNum, GridCountPerCycle, HeightMapParams);

	for (int i = 0; i < CycleNum; i++)
	{
		for (int j = 0; j < GridCountPerCycle; j++) {

			// adjust height
			GridPtrMap.GetElement(i, j)->SetActorScale3D(FVector(1, 1, heightMap.GetElement(i, j)));

			// whether is sand
			if (moistureMap.GetElement(i, j) < SandMoistureThreshold) {
				GridTypeMap.SetElement(i, j, static_cast<int>(GridType::SAND));
			}

			// whether is water
			if (moistureMap.GetElement(i, j) > WaterMoistureThreshold &&
				moistureMap.GetElement(i, j) < WaterHeightThreshold) {
				GridTypeMap.SetElement(i, j, static_cast<int>(GridType::WATER));
			}

			// update types and material
			UpdateAllGrids();

			// pollution
			GridPtrMap.GetElement(i, j)->SetPollutionPercent(pollutionMap.GetElement(i, j));
			if (pollutionMap.GetElement(i, j) > PollutionThreshold) {

				// do something with the material
				GridPtrMap.GetElement(i, j)->SetPolluted(PollutedMaterial);

			}

			// natural plants
			FRandomStream Stream(FMath::Rand());

			if (pollutionMap.GetElement(i, j) < PlantGrowthPollutionThreshold &&
				moistureMap.GetElement(i, j) > PlantGrowthMoistureThreshold) {
				
				float rnd = FMath::FRandRange(0.0, 1.0);
				if (rnd < PlantGrowthProb) {
					SpawnRandomPlant(FCoordinate2D{ i, j });
				}
			}
		}
	}
}

void AArmFarmManager::SpawnArmGrids()
{

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// math manually
	//TArray<FVector> locations;

	GridTypeMap.Init(CycleNum, GridCountPerCycle, -1);
	GridPtrMap.Init(CycleNum, GridCountPerCycle, nullptr);

	for (int j = 0; j < CycleNum; j++) {
		for (int i = 0; i < GridCountPerCycle; i++) {

			float thetaDegree = (float)i / (float)GridCountPerCycle * 360.0f;
			float thetaRadian = (float)i / (float)GridCountPerCycle * PI * 2.0f;

			float arc = sinf(thetaRadian / 2.0f) * ArmCalibre;
			float x = -1 * arc * cosf(thetaRadian / 2.0f);
			float y = j * 50;
			float z = arc * sinf(thetaRadian / 2.0f);

			FVector loc = FVector(x, y, z);
			FRotator rot = FRotator(-1 * thetaDegree, 0, 0);
			AFarmingGrid* grid = GetWorld()->SpawnActor<AFarmingGrid>(BP_GridActor, loc, rot, SpawnParameters);

			if (grid) {
				GridPtrMap.SetElement(j, i, grid);
				LocationGridMap.Add(loc, grid);
				GridTypeMap.SetElement(j, i, 0);
			}
		}
	}
	
}

