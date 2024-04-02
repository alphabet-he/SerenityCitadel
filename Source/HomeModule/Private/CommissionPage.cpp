// Fill out your copyright notice in the Description page of Project Settings.


#include "CommissionPage.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UCommissionPage::NativeConstruct()
{
	Super::NativeConstruct();

	CarlyCommissionButton->OnClicked.AddUniqueDynamic(this, &UCommissionPage::ClickCommissionDetail);
	AcceptButton->OnClicked.AddUniqueDynamic(this, &UCommissionPage::AcceptCommission);
}

void UCommissionPage::ClickCommissionDetail()
{
	if (CarlyCommissionDetail->GetVisibility() == ESlateVisibility::Visible) {
		CarlyCommissionDetail->SetVisibility(ESlateVisibility::Hidden);
		BlockButton->SetVisibility(ESlateVisibility::Hidden);
		AcceptButton->SetVisibility(ESlateVisibility::Hidden);
		RejectButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		CarlyCommissionDetail->SetVisibility(ESlateVisibility::Visible);
		BlockButton->SetVisibility(ESlateVisibility::Visible);
		AcceptButton->SetVisibility(ESlateVisibility::Visible);
		RejectButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCommissionPage::AcceptCommission()
{
}
