// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotMinimap.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"

// Sets default values
ARobotMinimap::ARobotMinimap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	MinimapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Minimap Mesh"));
	MinimapMesh->SetupAttachment(RootComponent);

	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Minimap Scene Capture Comp"));
	SceneCaptureComp->SetupAttachment(RootComponent);

	MinimapPawnStartPos = CreateDefaultSubobject<UBoxComponent>(TEXT("Minimap Pawn Start Pos"));
	MinimapPawnStartPos->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARobotMinimap::BeginPlay()
{
	Super::BeginPlay();
	
}



