// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerDesktop.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "MyGameInstanceSubsystem.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>


void UComputerDesktop::NativeConstruct()
{
	Super::NativeConstruct();

	CommissionButton->OnClicked.AddUniqueDynamic(this, &UComputerDesktop::OpenCommissionPage);
	MarketButton->OnClicked.AddUniqueDynamic(this, &UComputerDesktop::OpenMarketPage);
	VanButton->OnClicked.AddUniqueDynamic(this, &UComputerDesktop::OpenVanPage);

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	GameInstanceSubsystem = Cast<UMyGameInstanceSubsystem>(
		GetWorld()->GetGameInstance()->GetSubsystem<UMyGameInstanceSubsystem>()
	);
	check(GameInstanceSubsystem);

	PlayerCharacter = HomeGameMode->GetPlayerCharacter();
}


void UComputerDesktop::OpenCommissionPage()
{
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	HomeGameMode->HomeWidgetManager->ShowCommissionPage();
}

void UComputerDesktop::OpenMarketPage()
{
}

void UComputerDesktop::OpenVanPage()
{
}

void UComputerDesktop::UpdateDate()
{
}
