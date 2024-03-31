// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeleporterWidget.generated.h"


/**
 * 
 */

class UButton;
class APlayerControllerTest;

UCLASS()
class UTeleporterWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	UButton* FarmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BattlefieldButton;

	UPROPERTY(meta = (BindWidget))
	UButton* WastelandButton;

private:
	APawn* PlayerCharacter = nullptr;
	APlayerControllerTest* PlayerController = nullptr;

	UPROPERTY(EditAnywhere)
	FVector FarmDestination;

	UPROPERTY(EditAnywhere)
	FVector HomeDestination;

	UPROPERTY(EditAnywhere)
	FVector BattlefieldDestination;

	UPROPERTY(EditAnywhere)
	FVector WastelandDestination;


private:
	void NativeConstruct() override;

	UFUNCTION()
	void ToFarm();

	UFUNCTION()
	void ToHome();

	UFUNCTION()
	void ToBattlefield();

	UFUNCTION()
	void ToWasteland();

	void HideWidget();
};
