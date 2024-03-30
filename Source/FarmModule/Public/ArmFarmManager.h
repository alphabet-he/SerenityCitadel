// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmFarmManager.generated.h"

class AFarmingGrid;

UCLASS()
class FARMMODULE_API AArmFarmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmFarmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ReferenceMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFarmingGrid> BP_GridActor;

private:
	

private:
	void GenerateArmMap();

};
