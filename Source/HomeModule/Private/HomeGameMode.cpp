// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "RobotMinimap.h"
#include "MinimapPawn.h"
#include "CommissionButton.h"
#include "RobotToRepair.h"
#include "MyGameInstanceSubsystem.h"
#include "MinimapController.h"
#include "MainRobot.h"

void AHomeGameMode::StartPlay()
{
	Super::StartPlay();

	DesktopWidget = CreateWidget<UComputerDesktop>(GetWorld(), DesktopWidgetClass);
	DesktopWidget->RemoveFromParent();

	CommissionPageWidget = CreateWidget<UCommissionPage>(GetWorld(), CommissionPageWidgetClass);
	CommissionPageWidget->RemoveFromParent();

	InTransitWidget = CreateWidget<UInTransitWidget>(GetWorld(), InTransitWidgetClass);
	InTransitWidget->RemoveFromParent();

	DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
	DialogueWidget->RemoveFromParent();

	ControlPanelWidget = CreateWidget<UControlPanelWidget>(GetWorld(), ControlPanelWidgetClass);
	ControlPanelWidget->RemoveFromParent();

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPlayerCharacter());
	check(PlayerCharacter);

	MyGameInstanceSubsystem = Cast<UMyGameInstanceSubsystem>(
		GetWorld()->GetGameInstance()->GetSubsystem<UMyGameInstanceSubsystem>()
	);
	check(MyGameInstanceSubsystem);

	MyGameInstanceSubsystem->PlayerCharacter = PlayerCharacter;
	MyGameInstanceSubsystem->bStartFromHome = true;

	MainRobot = Cast<AMainRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainRobot::StaticClass()));
	check(MainRobot);
}

void AHomeGameMode::SpawnMinimapPawn()
{
	if (!minimap) return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector spawnLoc = minimap->GetPawnSpawnPos();

	minimapPawn = GetWorld()->SpawnActor<AMinimapPawn>(
		MinimapPawnClass, minimap->GetPawnSpawnPos(), FRotator(0), SpawnParameters);
	if (minimapPawn) {
		minimapPawn->SetForwardDirection(minimap->GetForwardDirection());
		minimapPawn->SetRightDirection(minimap->GetRightDirection());
		
		PlayerCharacter->SetControllingMinimapPawn(true);
		PlayerCharacter->SetControlledMinimapPawn(minimapPawn);
	}
	
	


}

void AHomeGameMode::CommissionSpawn(UCommissionButton* commissionButton)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	robotInRepair = GetWorld()->SpawnActor<ARobotToRepair>(
		commissionButton->RobotClass, RobotPosOnTable, FRotator(90.0f, 90.0f, 0), SpawnParameters);
	if (robotInRepair) {
		// change the pos of E to talk widget

	}
	MyGameInstanceSubsystem->RobotInRepair = robotInRepair;

	minimap = GetWorld()->SpawnActor<ARobotMinimap>(
		commissionButton->RobotMinimapClass, FVector(1000.0f, 1000.0f, -3000.0f), FRotator(0), SpawnParameters);

	LevelToLoad = commissionButton->LevelToLoad;
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);

	ASerenityCitadelCharacter* MicroRobotCharacter = GetWorld()->SpawnActor<ASerenityCitadelCharacter>(
		MicroRobotCharacterClass, MicroRobotSpawnPosInFarm, FRotator(0, 0, 0), SpawnParameters);


	if (MicroRobotCharacter) {
		MyGameInstanceSubsystem->MicroRobotList.Add(LevelToLoad, MicroRobotCharacter);
	}

	MainRobot->SetPriorityDialogue(commissionButton->DialogueWithMainRobotBeforeFix);
}

void AHomeGameMode::DestroyMinimapPawn()
{
	if (minimapPawn) {
		minimapPawn->K2_DestroyActor();
		minimapPawn = nullptr;
	}
	PlayerCharacter->SetControllingMinimapPawn(false);
	PlayerCharacter->SetControlledMinimapPawn(nullptr);
}

void AHomeGameMode::OnRobotFixed()
{
	robotInRepair->OnFixed();
	robotInRepair->SetActorLocation(RobotPosStand);
	robotInRepair->SetActorRotation(FQuat(0));
}
