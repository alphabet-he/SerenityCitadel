// Fill out your copyright notice in the Description page of Project Settings.


#include "GridButton.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <OperatingWidget.h>

UGridButton::UGridButton()
{
	OnClicked.AddDynamic(this, &UGridButton::OnClick);

	//Bind function
	click.AddDynamic(this, &UGridButton::ClickFunction);
}

void UGridButton::OnClick()
{
	click.Broadcast(Row, Column);
}

void UGridButton::ClickFunction(int32 _row, int32 _column)
{
	/** load stuff here **/
	UE_LOG(LogTemp, Warning, TEXT("Row: %i, Column: %i"), _row, _column);
	
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UOperatingWidget::StaticClass(), true);

	widgetInstance = Cast<UOperatingWidget>(Widgets[0]);

	check(widgetInstance);

	widgetInstance->GridButtonClicked(_row, _column);

}
