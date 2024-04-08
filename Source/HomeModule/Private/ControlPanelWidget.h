// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ControlPanelWidget.generated.h"

/**
 * 
 */
class AHomeGameMode;
class APlayerControllerTest;
class APlayerCharacter;

UCLASS()
class UControlPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* ZoomInButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DispatchButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RecallButton;

	AHomeGameMode* HomeGameMode;

	APlayerControllerTest* PlayerController;

	APlayerCharacter* PlayerCharacter;

private:
	void NativeConstruct() override;

	UFUNCTION()
	void ClickZoomInButton();

	UFUNCTION()
	void ClickDispatchButton();

	UFUNCTION()
	void ClickRecallButton();

public:
	void EnableZoomInButton() {
		ZoomInButton->SetIsEnabled(true);
	};

	void DisableZoomInButton() {
		ZoomInButton->SetIsEnabled(false);
	};
};
