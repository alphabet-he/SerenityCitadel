// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommissionPage.generated.h"

/**
 * 
 */

class UButton;
class UImage;

UCLASS()
class UCommissionPage : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UButton* CarlyCommissionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BlockButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RejectButton;

	UPROPERTY(meta = (BindWidget))
	UImage* CarlyCommissionDetail;

private:
	void NativeConstruct() override;

	UFUNCTION()
	void ClickCommissionDetail();

	UFUNCTION()
	void AcceptCommission();
	
};
