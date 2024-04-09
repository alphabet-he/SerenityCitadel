// Fill out your copyright notice in the Description page of Project Settings.


#include "GridOperationButton.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <OperatingWidget.h>
#include <Kismet/GameplayStatics.h>
#include <FarmingSubsystem.h>

UGridOperationButton::UGridOperationButton()
{
	OnClicked.AddDynamic(this, &UGridOperationButton::OnClick);

	//Bind function
	click.AddDynamic(this, &UGridOperationButton::ClickFunction);

}

void UGridOperationButton::OnClick()
{
	if (!subsystem) {
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		subsystem = gameInstance->GetSubsystem<UFarmingSubsystem>();
	}
	if (subsystem) {
		FGridTransitionWrapper* wrapper = subsystem->GridTransitionMapping.Find(_GridType);
		if (wrapper) {
			EGridType* type = wrapper->OperationMapping.Find(Operation);
			click.Broadcast(Row, Column, *type);
		}
	}

	
	
}

void UGridOperationButton::ClickFunction(int32 _row, int32 _column, EGridType type)
{
	/** load stuff here **/
	UE_LOG(LogTemp, Warning, TEXT("Row: %i, Column: %i, Changing to new type"), _row, _column);

	subsystem->ChangeGrid(FCoordinate2D{ _row, _column }, type);

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UOperatingWidget::StaticClass(), true);

	widgetInstance = Cast<UOperatingWidget>(Widgets[0]);

	check(widgetInstance);

	widgetInstance->SetWidgetToDefault();
}