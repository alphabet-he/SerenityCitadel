// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonFarmManager.h"
#include "ArmFarmManager.generated.h"

class AFarmingGrid;

UCLASS()
class FARMMODULE_API AArmFarmManager : public ACommonFarmManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmFarmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFarmingGrid> BP_GridActor;

	UPROPERTY(EditAnywhere)
	float ArmCalibre = 3000;

	UPROPERTY(EditAnywhere)
	int GridCountPerCycle = 200;

	UPROPERTY(EditAnywhere)
	int CycleNum = 50;

	UPROPERTY(EditAnywhere)
	float PlantGrowthMoistureThreshold = 0.5f;

	UPROPERTY(EditAnywhere)
	float PlantGrowthPollutionThreshold = 0.2f;

public:
	UFUNCTION(BlueprintCallable)
	void GenerateGeometry(
		FNoiseMapParams HeightMapParams, // grid scale-z
		FNoiseMapParams MoistureMapParams, // from 0 to 1
		FNoiseMapParams PollutionMapParams, // from 0 to 1
		float SandMoistureThreshold, // less than moisture
		float WaterMoistureThreshold, // greater than moisture
		float WaterHeightThreshold, // lower than moisture
		float PollutionThreshold, // larger than pollution
		float PlantGrowthProb // natural plants
	);

private:
	void SpawnArmGrids();

};
