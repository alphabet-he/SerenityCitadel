// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommissionPage.generated.h"

/**
 * 
 */

class UButton;
class UImage;
class AHomeGameMode;
class APlayerControllerTest;
class ASerenityCitadelCharacter;
class UCommissionButton;
class ARobotToRepair;
class UMyGameInstanceSubsystem;

UCLASS()
class UCommissionPage : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UCommissionButton* CarlyCommissionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BlockButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RejectButton;

	UPROPERTY(meta = (BindWidget))
	UImage* CarlyCommissionDetail;

	AHomeGameMode* HomeGameMode;

	APlayerControllerTest* PlayerController;

	ASerenityCitadelCharacter* PlayerCharacter;

	TSubclassOf<ARobotToRepair> currRobotClass = nullptr;

	UMyGameInstanceSubsystem* GameInstanceSubsystem;

public:
	void SetCurrRobotClass(TSubclassOf<ARobotToRepair> robotClass);

private:
	void NativeConstruct() override;

	UFUNCTION()
	void ClickCommissionDetail();

	UFUNCTION()
	void AcceptCommission();

	UFUNCTION()
	void CommissionAcceptedEnd();
	
};
