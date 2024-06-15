// Fill out your copyright notice in the Description page of Project Settings.


#include "ExhibitionPawn.h"
#include "ExhibitionFarmManager.h"
#include "ExhibitionGameMode.h"
#include "ExhibitionGrid.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AExhibitionPawn::AExhibitionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExhibitionPawn::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yes AI Controller"));
		AIController->MoveToLocation(GetActorLocation() + FVector(250, 0, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No AI Controller"));
	}
	
}

void AExhibitionPawn::WalkTo(int row, int column)
{
	if (!ExhibitionFarmManager) {
		AExhibitionGameMode* ExhibitionGameMode = Cast<AExhibitionGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		ExhibitionFarmManager = ExhibitionGameMode->ExhibitionFarmManager;
	}
	FVector start = GetActorLocation();
	FVector target = ExhibitionFarmManager->GetGridPtrMap().GetElement(row, column)->GetActorLocation();

}

// Called every frame
void AExhibitionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExhibitionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

