// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TArray2D.h"
#include "OperatingWidget.generated.h"


/**
 * 
 */


class UGridPanel;
class UTextBlock;
class UFarmingSubsystem;
class UVerticalBox;
class UButton;
enum class EGridType : uint8;

UCLASS()
class FARMMODULE_API UOperatingWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UGridPanel* GridPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrGridType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GridRow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GridCol;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OperationVerticalBox;

private:
	void NativeConstruct() override;

	UFarmingSubsystem* farmingSystem;

	TArray<UButton*> ButtonsInVerticalBox;

	TArray2D<UButton*> GridButtons;

public:
	void GridButtonClicked(int32 row, int32 col);

	void SetWidgetToDefault();

	void UpdateGridButtonColor(int32 row, int32 col);
	
};
