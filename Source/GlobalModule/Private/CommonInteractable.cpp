// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonInteractable.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerControllerTest.h"

// Sets default values
ACommonInteractable::ACommonInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleporter Mesh"));
	InteractableMesh->SetupAttachment(RootComponent);

	EToInteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	EToInteractWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACommonInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	EToInteractWidget->SetVisibility(false);

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);
}

void ACommonInteractable::Tick(float DeltaTime)
{
}

void ACommonInteractable::EnterPlayerInteractionBox()
{
}

void ACommonInteractable::LeavePlayerInteractionBox()
{
}

