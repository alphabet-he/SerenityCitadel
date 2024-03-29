// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingGrid.h"


// Sets default values
AFarmingGrid::AFarmingGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	SetRootComponent(GridMesh);
	
}

// Called when the game starts or when spawned
void AFarmingGrid::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* GameInst = GetGameInstance();
	FarmingSubsystem = GameInst->GetSubsystem<UFarmingSubsystem>();
	int scale = FarmingSubsystem->GridScale;
	GridMesh->SetStaticMesh(Mesh);
	GridMesh->SetWorldScale3D(FVector(scale, scale, scale));
}

// Called every frame
void AFarmingGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFarmingGrid::UpdateGrid()
{
	check(FarmingSubsystem);
	if (gridType == -1) return;
	if (GridMesh)
	{
		UMaterial* m = FarmingSubsystem->GridTextures[gridType];
		int numberOfMaterials = GridMesh->GetNumMaterials();
		for (int index = 0; index < numberOfMaterials; index++)
		{
			if (GridMesh->GetMaterial(index))
			{
				GridMesh->SetMaterial(index, m);
			}
		}
	}

}

