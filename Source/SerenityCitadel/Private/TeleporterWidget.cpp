// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterWidget.h"
#include "Components/Button.h"
#include <SerenityCitadel/PlayerControllerTest.h>
#include <Kismet/GameplayStatics.h>

void UTeleporterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = PlayerController->GetPawn();

	check(PlayerCharacter);

	FarmButton->OnClicked.AddUniqueDynamic(this, &UTeleporterWidget::ToFarm);
	HomeButton->OnClicked.AddUniqueDynamic(this, &UTeleporterWidget::ToHome);
	BattlefieldButton->OnClicked.AddUniqueDynamic(this, &UTeleporterWidget::ToBattlefield);
	WastelandButton->OnClicked.AddUniqueDynamic(this, &UTeleporterWidget::ToWasteland);
}

void UTeleporterWidget::ToFarm()
{
	PlayerCharacter->SetActorLocation(FarmDestination);
}

void UTeleporterWidget::ToHome()
{
	PlayerCharacter->SetActorLocation(HomeDestination);
}

void UTeleporterWidget::ToBattlefield()
{
	PlayerCharacter->SetActorLocation(BattlefieldDestination);
}

void UTeleporterWidget::ToWasteland()
{
	PlayerCharacter->SetActorLocation(WastelandDestination);
}

void UTeleporterWidget::HideWidget()
{
	
}




