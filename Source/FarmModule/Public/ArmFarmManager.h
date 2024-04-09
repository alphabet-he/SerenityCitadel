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

	UPROPERTY(EditAnywhere)
	FVector GridStartPos;

public:
	UFUNCTION(BlueprintCallable)
	void GenerateGeometry(
		FNoiseMapParams HeightMapParams, // grid scale-z
		FNoiseMapParams MoistureMapParams, // from 0 to 1
		FNoiseMapParams PollutionMapParams, // from 0 to 1
		float _sandMoistureThreshold, // less than moisture
		float _waterMoistureThreshold, // greater than moisture
		float _waterHeightThreshold, // lower than moisture
		float _pollutionThreshold, // larger than pollution
		float plantGrowthProb // natural plants
	);

private:
	void SpawnArmGrids();

};
