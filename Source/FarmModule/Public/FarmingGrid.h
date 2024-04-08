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
	AGroundEntity* EntityAbove = nullptr;
	
	UPROPERTY()
	UFarmingSubsystem* FarmingSubsystem = nullptr;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int gridType = -1;

	bool bPolluted = false;

	float PollutionPercent = 0;

public:	

	void setPlant(AGroundEntity* plantPtr) { EntityAbove = plantPtr; };

	AGroundEntity* getPlant() { return EntityAbove; };

	void setGridType(GridType i) { gridType = static_cast<int>(i); };

	int getGridType() { return gridType; };

	void UpdateGrid();

	void UpdateGrid(UMaterial* material);

	void UpdateGrid(UMaterialInstance* material);

	void SetPolluted(UMaterial* material);

	void ClearPolluted();

	FORCEINLINE void SetPollutionPercent(float percent) {
		PollutionPercent = percent;
	}

	FORCEINLINE float GetPollutionPercent() {
		return PollutionPercent;
	}

};
