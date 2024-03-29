// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSubsystemController.h"
#include "FarmModuleEnums.h"

// Sets default values
AFarmingSubsystemController::AFarmingSubsystemController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GridTextures.Init(nullptr, static_cast<int>(GridType::Count));
}

// Called when the game starts or when spawned
void AFarmingSubsystemController::BeginPlay()
{
	Super::BeginPlay();
	
}


