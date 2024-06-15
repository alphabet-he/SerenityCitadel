// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExhibitionPawn.generated.h"

class AExhibitionFarmManager;
class AAIController;

UCLASS()
class AExhibitionPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExhibitionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void WalkTo(int row, int column);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	AExhibitionFarmManager* ExhibitionFarmManager;

private:
	AAIController* AIController;
};
