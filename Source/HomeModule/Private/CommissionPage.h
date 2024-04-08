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
class ARobotMinimap;
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
	UButton* CompleteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* WithdrawButton;

	UPROPERTY(meta = (BindWidget))
	UImage* CarlyCommissionDetail;

	UPROPERTY(meta = (BindWidget))
	UImage* AcceptedStatus;

	AHomeGameMode* HomeGameMode;

	APlayerControllerTest* PlayerController;

	ASerenityCitadelCharacter* PlayerCharacter;

	UCommissionButton* currCommissionButton = nullptr;

	// for a list of commissions, make these two bool into array
	bool bDealt = false;
	bool bAccepted = false;

public:
	void SetCurrCommissionButton(UCommissionButton* commissionButton);

private:
	void NativeConstruct() override;

	UFUNCTION()
	void ClickCommissionDetail();

	UFUNCTION()
	void AcceptCommission();

	UFUNCTION()
	void CommissionAcceptedEnd();
	
};
