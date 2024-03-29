// Fill out your copyright notice in the Description page of Project Settings.


#include "OperatingWidget.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include <FarmingSubsystem.h>
#include <Kismet/GameplayStatics.h>
#include <TArray2D.h>
#include "Components/GridSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateTypes.h"
#include "FarmModuleEnums.h"
#include <GridButton.h>
#include "Internationalization/Text.h"
#include <Components/VerticalBox.h>
#include <GridOperationButton.h>

#define LOCTEXT_NAMESPACE "OperatingWidget"

void UOperatingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	farmingSystem = gameInstance->GetSubsystem<UFarmingSubsystem>();
	
	TArray2D<int> gridMap = farmingSystem->GetGridMap();
	int mapRow = gridMap.GetRow();
	int mapCol = gridMap.GetColumn();

	GridButtons.Init(mapRow, mapCol, nullptr);

	// decide button size
	
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(GridPanel->Slot);
	int widthSize = PanelSlot->GetSize().X / mapCol;
	int heightSize = PanelSlot->GetSize().Y / mapRow;
	int buttonSize = FMath::Min(widthSize, heightSize);


	FButtonStyle MyButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	MyButtonStyle.Normal.ImageSize = FVector2D(buttonSize, buttonSize);
	MyButtonStyle.Hovered.ImageSize = FVector2D(buttonSize, buttonSize);
	MyButtonStyle.Pressed.ImageSize = FVector2D(buttonSize, buttonSize);

	// put buttons
	for (int i = 0; i < gridMap.GetRow(); i++) {
		for (int j = 0; j < gridMap.GetColumn(); j++) {
			
			// create button
			UGridButton* Button = NewObject<UGridButton>(GridPanel);
			Button->Row = i;
			Button->Column = j;

			GridButtons.SetElement(i, j, Button);
			Button->SetStyle(MyButtonStyle);
			UpdateGridButtonColor(i, j);
			
			UGridSlot* GridSlot = Cast<UGridSlot>(GridPanel->AddChildToGrid(Button));
			GridSlot->SetRow(i);
			GridSlot->SetColumn(j);
		}
	}
}

void UOperatingWidget::GridButtonClicked(int32 row, int32 col)
{
	
	FString EnumName = StaticEnum<GridType>()->GetNameByValue(farmingSystem->GetGridMap().GetElement(row, col)).ToString();
	CurrGridType->SetText(FText::FromString(EnumName));

	// Define the format string using LOCTEXT
	FText FormatString = LOCTEXT("RowTextFormat", "Row: {0}");

	// Use FText::Format to replace {0} with the row number
	FText FormattedText = FText::Format(FormatString, FText::AsNumber(row));

	// Set the text on your GridRow object
	GridRow->SetText(FormattedText);
	
	FormatString = LOCTEXT("ColumnTextFormat", "Column: {0}");
	FormattedText = FText::Format(FormatString, FText::AsNumber(col));
	GridCol->SetText(FormattedText);

	for (UButton* buttonToRemove : ButtonsInVerticalBox) {
		buttonToRemove->RemoveFromParent();
	}
	ButtonsInVerticalBox.Empty();
	
	GridType _gridType = static_cast<GridType>(farmingSystem->GetGridMap().GetElement(row, col));
	FGridTransitionWrapper* wrapper = farmingSystem->GridTransitionMapping.Find(_gridType);
	if (wrapper) {
		for (const auto& it : wrapper->OperationMapping)
		{
			UGridOperationButton* Button = NewObject<UGridOperationButton>(OperationVerticalBox);
			Button->Row = row;
			Button->Column = col;
			Button->_GridType = _gridType;
			Button->Operation = it.Key;
			UTextBlock* TextBlock = NewObject<UTextBlock>(Button);
			FString name_s = StaticEnum<GridOperation>()->GetNameByValue((int)it.Key).ToString();
			FString CleanEnumName = name_s.Right(name_s.Len() - name_s.Find("::") - 2);
			TextBlock->SetText(FText::FromString(CleanEnumName));
			Button->AddChild(TextBlock);
			OperationVerticalBox->AddChildToVerticalBox(Button);
			ButtonsInVerticalBox.Add(Button);
		}
	}
	

	


}

void UOperatingWidget::SetWidgetToDefault()
{
	CurrGridType->SetText(FText::FromString("GridType"));
	GridRow->SetText(FText::FromString("Row"));
	GridCol->SetText(FText::FromString("Column"));
	for (UButton* buttonToRemove : ButtonsInVerticalBox) {
		buttonToRemove->RemoveFromParent();
	}
	ButtonsInVerticalBox.Empty();

}

void UOperatingWidget::UpdateGridButtonColor(int32 row, int32 col)
{
	UButton* ButtonToUpdate = GridButtons.GetElement(row, col);

	check(ButtonToUpdate);

	TArray2D<int> gridMap = farmingSystem->GetGridMap();

	FButtonStyle MyButtonStyle = ButtonToUpdate->GetStyle();

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::WATER)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Blue);
	}

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::SAND)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Yellow);
	}

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::ROCK)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Red);
	}

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::SOIL)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Gray);
	}

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::PIT)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::White);
	}

	if (gridMap.GetElement(row, col) == static_cast<int>(GridType::FARMLAND)) {
		MyButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	}

	ButtonToUpdate->SetStyle(MyButtonStyle);
}

#undef LOCTEXT_NAMESPACE

