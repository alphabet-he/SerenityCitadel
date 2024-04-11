// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotMinimap.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MinimapPawn.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>

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

	TargetPos = CreateDefaultSubobject<UBoxComponent>(TEXT("Target Pos"));
	TargetPos->SetupAttachment(RootComponent);

	ForwardDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Minimap Forward Direction"));
	ForwardDirection->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void ARobotMinimap::BeginPlay()
{
	Super::BeginPlay();

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	// Bind function
	TargetPos->OnComponentBeginOverlap.AddDynamic(this, &ARobotMinimap::ArriveAtTarget);
	TargetPos->OnComponentEndOverlap.AddDynamic(this, &ARobotMinimap::LeaveTarget);
	
}

void ARobotMinimap::ArriveAtTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMinimapPawn>(OtherActor)) {
		HomeGameMode->HomeWidgetManager->ControlPanelWidget->EnableZoomInButton();
	}
}

void ARobotMinimap::LeaveTarget(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMinimapPawn>(OtherActor)) {
		HomeGameMode->HomeWidgetManager->ControlPanelWidget->DisableZoomInButton();
	}
}




