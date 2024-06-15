// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundEntity.h"
#include "FarmingSubsystem.h"
#include "FarmModuleEnums.h"
#include "FarmingGrid.generated.h"

class UArrowComponent;

UCLASS()
class FARMMODULE_API AFarmingGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmingGrid();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GridMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UArrowComponent* PlantMark = nullptr;

private:
	
	UPROPERTY()
	UFarmingSubsystem* FarmingSubsystem = nullptr;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	EGridType GridType = EGridType::UNDEFINED;

	bool bPolluted = false;

	float PollutionPercent = 0;

	float MoisturePercent = 0;

	float Height = 0;

	bool bDigged = false;

	AGroundEntity* EntityAbove = nullptr;

	UPROPERTY(VisibleAnywhere)
	FCoordinate2D coordinate{-1, -1};

public:	

	void setGridType(EGridType i) { GridType = i; };

	void UpdateGrid();

	void UpdateGrid(UMaterial* material);

	void UpdateGrid(UMaterialInstance* material);

	void UpdatePolluted(UMaterialInstance* material);

	void ClearPolluted();

};
