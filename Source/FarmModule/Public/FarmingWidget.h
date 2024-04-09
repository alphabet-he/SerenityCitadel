// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "FarmingWidget.generated.h"

/**
 * 
 */

UCLASS()
class FARMMODULE_API UFarmingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* BatteryBar;

	UPROPERTY(meta = (BindWidget))
	UImage* WaterBar;

	UPROPERTY(meta = (BindWidget))
	UImage* PurifierBar;

	UPROPERTY(EditAnywhere)
	TArray<UImage*> SeedIcons;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Height;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Moisture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Pollution;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GrowingProb;

	UPROPERTY(meta = (BindWidget))
	UImage* Dry;

	UPROPERTY(meta = (BindWidget))
	UImage* Polluted;

	UPROPERTY(meta = (BindWidget))
	UImage* GoodToGo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HintText;

	UPROPERTY(meta = (BindWidget))
	UImage* AnalysisPanel;

	UPROPERTY(meta = (BindWidget))
	UImage* HintTextBox;

public:
	void HideAnalysis() {
		AnalysisPanel->SetVisibility(ESlateVisibility::Hidden);
		Height->SetVisibility(ESlateVisibility::Hidden);
		Moisture->SetVisibility(ESlateVisibility::Hidden);
		GrowingProb->SetVisibility(ESlateVisibility::Hidden);
		Dry->SetVisibility(ESlateVisibility::Hidden);
		Polluted->SetVisibility(ESlateVisibility::Hidden);
		GoodToGo->SetVisibility(ESlateVisibility::Hidden);
	}

	void ShowAnalysis() {
		AnalysisPanel->SetVisibility(ESlateVisibility::Visible);
		Height->SetVisibility(ESlateVisibility::Visible);
		Moisture->SetVisibility(ESlateVisibility::Visible);
		GrowingProb->SetVisibility(ESlateVisibility::Visible);
	}

	void HideHintText() {
		HintTextBox->SetVisibility(ESlateVisibility::Hidden);
		HintText->SetVisibility(ESlateVisibility::Hidden);
	}

	void ShowHintText() {
		HintTextBox->SetVisibility(ESlateVisibility::Visible);
		HintText->SetVisibility(ESlateVisibility::Visible);
	}


};
