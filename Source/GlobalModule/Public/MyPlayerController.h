// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerTest.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALMODULE_API AMyPlayerController : public APlayerControllerTest
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Farming")
	UInputAction* ActionExitFarm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Farming")
	UInputAction* ActionSwitchProp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Farming")
	UInputAction* ActionAnalyze = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Farming Actions Mapping")
	UInputMappingContext* FarmingMappingContent = nullptr;

public:
	void OnPossess(APawn* aPawn) override;

	void OnUnPossess() override;

};
