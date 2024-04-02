// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonInteractable.h"
#include "Computer.generated.h"

class AHomeGameMode;
class ASerenityCitadelCharacter;

UCLASS()
class AComputer : public ACommonInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	APlayerControllerTest* PlayerController;

	ASerenityCitadelCharacter* PlayerCharacter;

	AHomeGameMode* HomeGameMode;

private:
	virtual void InteractWithPlayer() override;

};
