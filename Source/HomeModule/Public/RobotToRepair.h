// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInteractable.h"
#include <StringArray.h>
#include "RobotToRepair.generated.h"

/**
 * 
 */

class AHomeGameMode;
class ASerenityCitadelCharacter;
class APlayerControllerTest;

UCLASS()
class HOMEMODULE_API ARobotToRepair : public ACommonInteractable
{
	GENERATED_BODY()

protected:
	bool bRepaired = false;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TArray<FString> PlayerDialoguesBeforeFixed;

	UPROPERTY(EditAnywhere)
	TArray<FString> RobotDialoguesBeforeFixed;
	
	UPROPERTY(EditAnywhere)
	TArray<FStringArray> PairedDialoguesBeforeFixed;

	UPROPERTY(EditAnywhere)
	TArray<FString> PlayerDialoguesAfterFixed;

	UPROPERTY(EditAnywhere)
	TArray<FString> RobotDialoguesAfterFixed;

	UPROPERTY(EditAnywhere)
	TArray<FStringArray> PairedDialoguesAfterFixed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	APlayerControllerTest* PlayerController;

	AHomeGameMode* HomeGameMode;

	ASerenityCitadelCharacter* PlayerCharacter;

	bool bCanInteract = true;

private:
	virtual void InteractWithPlayer() override;

	void ShowDialogue();

	void HideDialogue();

	void ChooseRandomDialogue(TArray<FString> PlayerDialogueArray, TArray<FString> RobotDialogueArray);

	void ChoosePairedDialogue(TArray<FStringArray> PairedDialogueArray);

	UFUNCTION()
	void ShowSecondDialogue();

};
