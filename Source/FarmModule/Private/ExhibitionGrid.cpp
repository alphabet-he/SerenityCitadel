// Fill out your copyright notice in the Description page of Project Settings.


#include "ExhibitionGrid.h"

AExhibitionGrid::AExhibitionGrid():AFarmingGrid()
{
	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraEffect->SetupAttachment(RootComponent);
}
