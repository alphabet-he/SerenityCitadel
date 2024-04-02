// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComputerDesktop.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UMyGameInstanceSubsystem;
class AHomeGameMode;
class UImage;
class ASerenityCitadelCharacter;

UCLASS()
class UComputerDesktop : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* VanButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CommissionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MarketButton;

	UPROPERTY(meta = (BindWidget))
	UImage* Month0;

	UPROPERTY(meta = (BindWidget))
	UImage* Month1;

	UPROPERTY(meta = (BindWidget))
	UImage* Day0;

	UPROPERTY(meta = (BindWidget))
	UImage* Day1;

	UMyGameInstanceSubsystem* GameInstanceSubsystem;

	AHomeGameMode* HomeGameMode;

	ASerenityCitadelCharacter* PlayerCharacter;

private:
	void NativeConstruct() override;

	UFUNCTION()
	void OpenCommissionPage();

	UFUNCTION()
	void OpenMarketPage();

	UFUNCTION()
	void OpenVanPage();

public:
	void UpdateDate();
};
