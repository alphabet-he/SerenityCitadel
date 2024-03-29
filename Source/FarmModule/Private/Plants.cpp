// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants.h"

// Sets default values
APlants::APlants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlants::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlants::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

