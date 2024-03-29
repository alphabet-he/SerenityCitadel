// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundEntity.h"
#include "Plants.generated.h"

UCLASS()
class FARMMODULE_API APlants : public AGroundEntity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlants();
	UPROPERTY()
	int PlantType = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
