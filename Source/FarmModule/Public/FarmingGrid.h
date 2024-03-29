// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundEntity.h"
#include "FarmingSubsystem.h"
#include "FarmModuleEnums.h"
#include "FarmingGrid.generated.h"


UCLASS()
class FARMMODULE_API AFarmingGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmingGrid();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* Mesh = nullptr;

private:
	UPROPERTY() 
	AGroundEntity* EntityAbove = nullptr;
	UPROPERTY()
	UStaticMeshComponent* GridMesh = nullptr;
	UPROPERTY()
	UFarmingSubsystem* FarmingSubsystem = nullptr;
	UPROPERTY() 
	int gridType = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setPlant(AGroundEntity* plantPtr) { EntityAbove = plantPtr; };
	AGroundEntity* getPlant() { return EntityAbove; };
	void setGridType(GridType i) { gridType = static_cast<int>(i); };
	int getGridType() { return gridType; };
	void UpdateGrid();
};
