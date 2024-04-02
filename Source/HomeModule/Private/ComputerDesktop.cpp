// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerDesktop.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "MyGameInstanceSubsystem.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "CommissionPage.h"
#include <Components/Image.h>
#include "SerenityCitadelCharacter.h"
#include "PlayerControllerTest.h"


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

	APlayerControllerTest* PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = PlayerController->GetPlayerCharacter();
	check(PlayerCharacter);
}


void UComputerDesktop::OpenCommissionPage()
{
	if (HomeGameMode->CommissionPageWidget) {
		HomeGameMode->CommissionPageWidget->AddToViewport();
		//HomeGameMode->DesktopWidget->RemoveFromViewport();
		PlayerCharacter->AddActiveWdiget(HomeGameMode->CommissionPageWidget);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Commission Page Instance"));
	}
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
