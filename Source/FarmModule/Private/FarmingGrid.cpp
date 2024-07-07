// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingGrid.h"
#include <Components/ArrowComponent.h>
#include <Plant.h>


// Sets default values
AFarmingGrid::AFarmingGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grid Mesh"));
	GridMesh->SetupAttachment(RootComponent);

	PlantMark = CreateDefaultSubobject<UArrowComponent>(TEXT("Plant Growth Mark"));
	PlantMark->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AFarmingGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AFarmingGrid::UpdateGrid()
{
	UGameInstance* GameInst = GetGameInstance();
	FarmingSubsystem = GameInst->GetSubsystem<UFarmingSubsystem>();
	if(!FarmingSubsystem) return;
	if (GridType == EGridType::UNDEFINED) return;
	UMaterial* m = FarmingSubsystem->GridTextures[static_cast<int>(GridType)];
	UpdateGrid(m);

}

void AFarmingGrid::UpdateGrid(UMaterial* material)
{
	if (GridMesh)
	{
		int numberOfMaterials = GridMesh->GetNumMaterials();
		if (GridMesh->GetMaterial(0))
		{
			GridMesh->SetMaterial(0, material);
		}
	}
}

void AFarmingGrid::UpdateGrid(UMaterialInstance* material)
{
	if (GridMesh)
	{
		int numberOfMaterials = GridMesh->GetNumMaterials();
		if (GridMesh->GetMaterial(0))
		{
			GridMesh->SetMaterial(0, material);
		}
	}
}

void AFarmingGrid::UpdatePolluted(UMaterialInstance* material)
{
	if (GridMesh) {
		GridMesh->SetOverlayMaterial(material);
	}
	
}

void AFarmingGrid::ClearPolluted()
{
	bPolluted = false;
	if (GridMesh) {
		GridMesh->SetOverlayMaterial(nullptr);
	}
}

bool AFarmingGrid::PutEntityAbove(TSubclassOf<AGroundEntity> groundEntityType)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EntityAbove = GetWorld()->SpawnActor<AGroundEntity>(groundEntityType,
		PlantMark->GetComponentLocation(), FRotator(0, 0, 0), SpawnParameters);

	if (EntityAbove) {
		return true;
	}
	else {
		return false;
	}
}

