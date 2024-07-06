// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundEntity.h"
#include "Plant.generated.h"

UCLASS()
class FARMMODULE_API APlant : public AGroundEntity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	int PlantType = -1;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> GrowthStateModels;

	UPROPERTY()
	int CurrentGrowthState = 0;

	UFUNCTION(BlueprintCallable)
	bool Grow(bool bExecute = true);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
