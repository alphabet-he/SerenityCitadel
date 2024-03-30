// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmFarmManager.h"
#include "FarmingGrid.h"

// Sets default values
AArmFarmManager::AArmFarmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArmFarmManager::BeginPlay()
{
	Super::BeginPlay();
	GenerateArmMap();
	
}

// Called every frame
void AArmFarmManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArmFarmManager::GenerateArmMap()
{
	// spawn the reference class in somewhere invisible
	FVector Location(10000000.0f, 1000000000.0f, 100000000.0f);
	FRotator Rotation(0.0f);
	FActorSpawnParameters SpawnParameters;
	AActor* ReferenceActor = GetWorld()->SpawnActor<AActor>(ReferenceMesh, Location, Rotation, SpawnParameters);

	// from the reference actor, get static mesh components
	TArray<UStaticMeshComponent*> meshes;
	ReferenceActor->GetComponents<UStaticMeshComponent>(meshes);

	// get cnt
	int cnt = meshes.Num();

	// get locations and re-order them

	// get base location
	FVector base = meshes[0]->GetRelativeLocation();

	// separate left half and right half
	TArray<FVector> leftHalf;
	TArray<FVector> rightHalf;
	for (UStaticMeshComponent* curr : meshes) {
		FVector relativePos = curr->GetRelativeLocation() - base;
		if (relativePos.X <= 0) {
			leftHalf.Add(relativePos);
		}
		else {
			rightHalf.Add(relativePos);
		}
	}

	// sort
	leftHalf.Sort([](const FVector A, const FVector B) {
		return A.Y < B.Y;
		}
	);
	rightHalf.Sort([](const FVector A, const FVector B) {
		return A.Y > B.Y;
		}
	);



	// spawn grids for the arm map, according to the location data
	float currRot = 0;
	for (FVector currLoc : leftHalf) {
		Rotation = FRotator(0, currRot, 0);
		AFarmingGrid* grid = GetWorld()->SpawnActor<AFarmingGrid>(BP_GridActor, currLoc, Rotation, SpawnParameters);
		if (grid) {
		}
		currRot += 360 / cnt;
	}
	for (FVector currLoc : rightHalf) {
		Rotation = FRotator(0, currRot, 0);
		AFarmingGrid* grid = GetWorld()->SpawnActor<AFarmingGrid>(BP_GridActor, currLoc, Rotation, SpawnParameters);
		currRot += 360 / cnt;
	}
}

