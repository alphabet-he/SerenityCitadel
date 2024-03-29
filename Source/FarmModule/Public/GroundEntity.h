// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundEntity.generated.h"

UCLASS()
class FARMMODULE_API AGroundEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundEntity();

private:
	int EntityType = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setEntityType(int type) { EntityType = type; }
	int getEntityType() { return EntityType; }

};
