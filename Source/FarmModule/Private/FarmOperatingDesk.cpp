// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmOperatingDesk.h"
#include <Components/WidgetComponent.h>
#include <SerenityCitadel/PlayerControllerTest.h>
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include <OperatingWidget.h>

// Sets default values
AFarmOperatingDesk::AFarmOperatingDesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	RootComponent = _RootComponent;

	OperatingDeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleporter Mesh"));
	OperatingDeskMesh->SetupAttachment(RootComponent);

	EtoInteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("E to Interact Widget"));
	EtoInteractWidget->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AFarmOperatingDesk::BeginPlay()
{
	Super::BeginPlay();
	
	EtoInteractWidget->SetVisibility(false);

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	OperatingWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
}

// Called every frame
void AFarmOperatingDesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFarmOperatingDesk::EnterPlayerInteractionBox()
{
	//UE_LOG(LogTemp, Warning, TEXT("Entered!"));
	EtoInteractWidget->SetVisibility(true);
}

void AFarmOperatingDesk::LeavePlayerInteractionBox()
{
	EtoInteractWidget->SetVisibility(false);
	PlayerController->DisableMouseCursor();
	//OperatingWidget->SetVisibility(false);
	PlayerController->EnableMovement();
}

void AFarmOperatingDesk::InteractWithPlayer()
{
	if (OperatingWidgetVisible) {
		PlayerController->DisableMouseCursor();
		Cast<UOperatingWidget>(OperatingWidget)->SetWidgetToDefault();
		OperatingWidget->SetVisibility(ESlateVisibility::Collapsed);
		EtoInteractWidget->SetVisibility(true);
		PlayerController->EnableMovement();
		OperatingWidgetVisible = false;
	}
	else {
		
		EtoInteractWidget->SetVisibility(false);
		//OperatingWidget->SetVisibility(true);
		OperatingWidget->AddToViewport();
		OperatingWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->DisableMovement();
		PlayerController->EnableMouseCursor();
		OperatingWidgetVisible = true;
	}
}

