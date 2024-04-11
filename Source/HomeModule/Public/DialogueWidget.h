// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */

UCLASS()
class HOMEMODULE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerDialogue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TargetDialogue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TargetName;

	UPROPERTY(meta = (BindWidget))
	UImage* TargetDialogueBox;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerDialogueBox;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerDialogue(FString s) {
		PlayerDialogue->SetText(FText::FromString(s));
	};

	UFUNCTION(BlueprintCallable)
	void SetTargetDialogue(FString s) {
		TargetDialogue->SetText(FText::FromString(s));
	};

	UFUNCTION(BlueprintCallable)
	void SetTargetName(FString s) {
		TargetName->SetText(FText::FromString(s));
		return;
	};

	UFUNCTION(BlueprintCallable) 
	void ShowPlayerDialogue() {
		PlayerDialogueBox->SetVisibility(ESlateVisibility::Visible);
		PlayerDialogue->SetVisibility(ESlateVisibility::Visible);
	}

	UFUNCTION(BlueprintCallable)
	void HidePlayerDialogue() {
		PlayerDialogueBox->SetVisibility(ESlateVisibility::Hidden);
		PlayerDialogue->SetVisibility(ESlateVisibility::Hidden);
	}

	UFUNCTION(BlueprintCallable)
	void ShowTargetDialogue() {
		TargetDialogueBox->SetVisibility(ESlateVisibility::Visible);
		TargetDialogue->SetVisibility(ESlateVisibility::Visible);
		TargetName->SetVisibility(ESlateVisibility::Visible);
	}

	UFUNCTION(BlueprintCallable)
	void HideTargetDialogue() {
		TargetDialogueBox->SetVisibility(ESlateVisibility::Hidden);
		TargetDialogue->SetVisibility(ESlateVisibility::Hidden);
		TargetName->SetVisibility(ESlateVisibility::Hidden);
	}
};
