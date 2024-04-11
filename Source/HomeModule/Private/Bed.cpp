// Fill out your copyright notice in the Description page of Project Settings.


#include "Bed.h"
#include <Kismet/GameplayStatics.h>
#include "HomeGameMode.h"
#include "MyGameInstanceSubsystem.h"

void ABed::BeginPlay()
{
	Super::BeginPlay();

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);
}

void ABed::InteractWithPlayer()
{
	if (bCanInteract) {
		bCanInteract = false;
		HomeGameMode->GetPlayerController()->DisableMovementAndAction();
		HomeGameMode->GetMyGameInstanceSubsystem()->AddDate();
		HomeGameMode->HomeWidgetManager->DesktopWidget->UpdateDate();
		
		CameraManager = Cast<APlayerCameraManager>(
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

		CameraManager->StartCameraFade(0, 1, 1.5f, FLinearColor::Black, false, true);

		FTimerHandle Handle0;
		FTimerHandle Handle1;
		GetWorld()->GetTimerManager().SetTimer(Handle0, this, &ABed::CameraFadeIn, 2.5f);
		GetWorld()->GetTimerManager().SetTimer(Handle1, this, &ABed::EndFade, 5.0f);
	}
}

void ABed::CameraFadeIn()
{
	UE_LOG(LogTemp, Warning, TEXT("Fading In"));
	CameraManager->StartCameraFade(1, 0, 2.5f, FLinearColor::Black, false, true);
}

void ABed::EndFade()
{
	bCanInteract = true;
	HomeGameMode->GetPlayerController()->EnableMovementAndAction();
}
