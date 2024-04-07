// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerControllerTest.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	TeleporterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleporter Mesh"));
	TeleporterMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);

	TeleporterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Teleporter Widget"));
	TeleporterWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionWidget->SetVisibility(false);
	TeleporterWidget->SetVisibility(false);

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::EnterPlayerInteractionBox()
{
	//UE_LOG(LogTemp, Warning, TEXT("Entered!"));
	InteractionWidget->SetVisibility(true);
}

void ATeleporter::LeavePlayerInteractionBox()
{
	InteractionWidget->SetVisibility(false);
	PlayerController->DisableMouseCursor();
	TeleporterWidget->SetVisibility(false);
	PlayerController->EnableMovementAndAction();
}

void ATeleporter::InteractWithPlayer() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacted!"));

	if (TeleporterWidget->GetVisibleFlag()) {
		PlayerController->DisableMouseCursor();
		TeleporterWidget->SetVisibility(false);
		PlayerController->EnableMovementAndAction();
		//PlayerCharacter->EnableInput(PlayerController);
		//PlayerCharacter->bBlockInput = false;
	}
	else {
		InteractionWidget->SetVisibility(false);
		TeleporterWidget->SetVisibility(true);
		PlayerController->DisableMovementAndAction();
		PlayerController->EnableMouseCursor();
		//PlayerCharacter->GetMovementComponent();
		//DisableInput(PlayerController);
	}
	
}

