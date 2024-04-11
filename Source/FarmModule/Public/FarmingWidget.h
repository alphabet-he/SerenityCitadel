// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "Components/PanelSlot.h"
#include <Components/CanvasPanelSlot.h>
#include <Components/GridPanel.h>
#include "FarmingWidget.generated.h"

/**
 * 
 */

UCLASS()
class FARMMODULE_API UFarmingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UTexture2D* RedBar;

	UPROPERTY(EditAnywhere)
	UTexture2D* BlueBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusText;

	UPROPERTY(meta = (BindWidget))
	UImage* BatteryBar;

	UPROPERTY(meta = (BindWidget))
	UImage* WaterBar;

	UPROPERTY(meta = (BindWidget))
	UImage* PurifierBar;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* SeedGridPanel;

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
		Pollution->SetVisibility(ESlateVisibility::Hidden);
		GrowingProb->SetVisibility(ESlateVisibility::Hidden);
		Dry->SetVisibility(ESlateVisibility::Hidden);
		Polluted->SetVisibility(ESlateVisibility::Hidden);
		GoodToGo->SetVisibility(ESlateVisibility::Hidden);
	}

	void ShowAnalysis() {
		AnalysisPanel->SetVisibility(ESlateVisibility::Visible);
		Height->SetVisibility(ESlateVisibility::Visible);
		Moisture->SetVisibility(ESlateVisibility::Visible);
		Pollution->SetVisibility(ESlateVisibility::Visible);
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

	void HideAllSuggestions() {
		Dry->SetVisibility(ESlateVisibility::Hidden);
		Polluted->SetVisibility(ESlateVisibility::Hidden);
		GoodToGo->SetVisibility(ESlateVisibility::Hidden);
	}

	void UpdateBatteryBar(float percent) {
		BatteryBarSlot->SetSize(FVector2D(BarBaseLength * percent, BarBaseHeight));
	}

	void UpdateWaterBar(float percent) {
		WaterBarSlot->SetSize(FVector2D(BarBaseLength * percent, BarBaseHeight));
	}

	void UpdatePurifierBar(float percent) {
		PurifyBarSlot->SetSize(FVector2D(BarBaseLength * percent, BarBaseHeight));
	}

	void UseSeed() {
		SeedIcons.Top()->SetVisibility(ESlateVisibility::Hidden);
		SeedIcons.Pop();
	}

	void SetStatusText(FText text) {
		StatusText->SetText(text);
	}

	void BarFlashRed(UImage* Bar) {
		FlashingBar = Bar;
		Bar->SetBrushFromTexture(RedBar);

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, 
			&UFarmingWidget::BarReturnBlue, 1.0f);
	}

private:
	float BarBaseLength;
	float BarBaseHeight;

	UCanvasPanelSlot* BatteryBarSlot;
	UCanvasPanelSlot* WaterBarSlot;
	UCanvasPanelSlot* PurifyBarSlot;

	UImage* FlashingBar;

	TArray<UWidget*> SeedIcons;

	void NativeConstruct() override {

		Super::NativeConstruct();

		BatteryBarSlot = Cast<UCanvasPanelSlot>(BatteryBar->Slot);
		WaterBarSlot = Cast<UCanvasPanelSlot>(WaterBar->Slot);
		PurifyBarSlot = Cast<UCanvasPanelSlot>(PurifierBar->Slot);

		BarBaseLength = BatteryBarSlot->GetSize().X;
		BarBaseHeight = BatteryBarSlot->GetSize().Y;

		SeedIcons = SeedGridPanel->GetAllChildren();
	};

	void BarReturnBlue() {
		FlashingBar->SetBrushFromTexture(BlueBar);
	}

};
