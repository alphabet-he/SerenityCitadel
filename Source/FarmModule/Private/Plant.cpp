// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

bool APlant::Grow(bool bExecute)
{
	if (CurrentGrowthState == GrowthStateModels.Num() - 1) {
		return false;
	}
	if (bExecute) {
		CurrentGrowthState++;
		Mesh->SetStaticMesh(GrowthStateModels[CurrentGrowthState]);
	}
	
	return true;

}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	if (GrowthStateModels.Num() > 0 &&
		!Mesh->GetStaticMesh()) {
		Mesh->SetStaticMesh(GrowthStateModels[CurrentGrowthState]);
	}
}

// Called every frame
void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

