// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotToRepair.h"
#include <Kismet/GameplayStatics.h>
#include "HomeGameMode.h"

void ARobotToRepair::BeginPlay()
{
	Super::BeginPlay();

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	// seems like this begin play is called before game mode's start play,
	// so the player character and controller cannot be initialized
	PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	PlayerController = HomeGameMode->GetPlayerController();
}

void ARobotToRepair::InteractWithPlayer()
{
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}

	if (!bCanInteract) return;
	if (!HomeGameMode->DialogueWidget) return;

	if (PlayerCharacter->GetActiveWidgets().Contains(HomeGameMode->DialogueWidget)) {
		HideDialogue();
	}
	else {
		SetDialogue();
		ShowDialogue();
	}

	
}

void ARobotToRepair::SetDialogue()
{
	bCanInteract = false;

	FRandomStream Stream(FMath::Rand());

	HomeGameMode->DialogueWidget->SetTargetName(Name);

	/*
	* set dialogues
	*/ 

	// if there is priority dialogues
	if (PriorityPairedDialogues.StringArray.Num() > 0) {
		HomeGameMode->DialogueWidget->SetPlayerDialogue(PriorityPairedDialogues.StringArray[0]);
		HomeGameMode->DialogueWidget->SetTargetDialogue(PriorityPairedDialogues.StringArray[1]);
		PriorityPairedDialogues.StringArray.Empty();
		return;
	}


	// after fixed
	if (bRepaired) {

		// no set dialogues
		if (PlayerDialoguesAfterFixed.Num() == 0
			&& PairedDialoguesAfterFixed.Num() == 0) {

			HomeGameMode->DialogueWidget->SetPlayerDialogue("...");
			HomeGameMode->DialogueWidget->SetTargetDialogue("...");
		}

		// no paired dialogues
		if (PlayerDialoguesAfterFixed.Num() != 0
			&& PairedDialoguesAfterFixed.Num() == 0) {

			ChooseRandomDialogue(PlayerDialoguesAfterFixed, RobotDialoguesAfterFixed);

		}

		// no random dialogues
		if (PlayerDialoguesAfterFixed.Num() == 0
			&& PairedDialoguesAfterFixed.Num() != 0) {

			ChoosePairedDialogue(PairedDialoguesAfterFixed);
		}

		// both have
		if (PlayerDialoguesAfterFixed.Num() == 0
			&& PairedDialoguesAfterFixed.Num() == 0) {

			int totalNum = PlayerDialoguesAfterFixed.Num() + PairedDialoguesAfterFixed.Num();
			int rndInd = FMath::RandRange(0, totalNum - 1);

			if (rndInd < PlayerDialoguesAfterFixed.Num()) {
				ChooseRandomDialogue(PlayerDialoguesAfterFixed, RobotDialoguesAfterFixed);
			}
			else {
				ChoosePairedDialogue(PairedDialoguesAfterFixed);
			}

		}

	}

	// before fixed
	else {
		
		// no set dialogues
		if (PlayerDialoguesBeforeFixed.Num() == 0
			&& PairedDialoguesBeforeFixed.Num() == 0) {

			HomeGameMode->DialogueWidget->SetPlayerDialogue("...");
			HomeGameMode->DialogueWidget->SetTargetDialogue("...");
		}

		// no paired dialogues
		if (PlayerDialoguesBeforeFixed.Num() != 0
			&& PairedDialoguesBeforeFixed.Num() == 0) {

			ChooseRandomDialogue(PlayerDialoguesBeforeFixed, RobotDialoguesBeforeFixed);

		}

		// no random dialogues
		if (PlayerDialoguesBeforeFixed.Num() == 0
			&& PairedDialoguesBeforeFixed.Num() != 0) {

			ChoosePairedDialogue(PairedDialoguesBeforeFixed);
		}

		// both have
		if (PlayerDialoguesBeforeFixed.Num() == 0
			&& PairedDialoguesBeforeFixed.Num() == 0) {

			int totalNum = PlayerDialoguesBeforeFixed.Num() + PairedDialoguesBeforeFixed.Num();
			int rndInd = FMath::RandRange(0, totalNum - 1);

			if (rndInd < PlayerDialoguesBeforeFixed.Num()) {
				ChooseRandomDialogue(PlayerDialoguesBeforeFixed, RobotDialoguesBeforeFixed);
			}
			else {
				ChoosePairedDialogue(PairedDialoguesBeforeFixed);
			}

		}


	}

}

void ARobotToRepair::ShowDialogue() {
	/*
	* show dialogues
	*/

	// hide the second dialogue
	HomeGameMode->DialogueWidget->HideTargetDialogue();

	// show player's dialogue
	HomeGameMode->DialogueWidget->ShowPlayerDialogue();

	// add to player character's list
	PlayerCharacter->AddActiveWdiget(HomeGameMode->DialogueWidget);

	// show widget, disable movement
	HomeGameMode->DialogueWidget->AddToViewport();
	PlayerController->DisableMovementAndAction();
	HideInteractionWidget();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ARobotToRepair::ShowSecondDialogue, 1.0f);
}

void ARobotToRepair::HideDialogue()
{
	HomeGameMode->DialogueWidget->RemoveFromParent();
	PlayerCharacter->RemoveWidget(HomeGameMode->DialogueWidget);
	PlayerController->EnableMovementAndAction();
	ShowInteractionWidget();
}

void ARobotToRepair::ChooseRandomDialogue(TArray<FString> PlayerDialogueArray, TArray<FString> RobotDialogueArray)
{
	int rndInd = FMath::RandRange(0, PlayerDialogueArray.Num() - 1);
	HomeGameMode->DialogueWidget->SetPlayerDialogue(PlayerDialogueArray[rndInd]);

	rndInd = FMath::RandRange(0, RobotDialogueArray.Num() - 1);
	HomeGameMode->DialogueWidget->SetTargetDialogue(RobotDialogueArray[rndInd]);
}

void ARobotToRepair::ChoosePairedDialogue(TArray<FStringArray> PairedDialogueArray)
{
	int rndInd = FMath::RandRange(0, PairedDialogueArray.Num() - 1);
	HomeGameMode->DialogueWidget->SetPlayerDialogue(PairedDialogueArray[rndInd].StringArray[0]);
	HomeGameMode->DialogueWidget->SetTargetDialogue(PairedDialogueArray[rndInd].StringArray[1]);
}

void ARobotToRepair::ShowSecondDialogue()
{
	HomeGameMode->DialogueWidget->ShowTargetDialogue();
	bCanInteract = true;
}
