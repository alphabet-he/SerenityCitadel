// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapPawn.h"

// Sets default values
AMinimapPawn::AMinimapPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinimapPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinimapPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMinimapPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

