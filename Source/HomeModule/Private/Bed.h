// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInteractable.h"
#include "Bed.generated.h"

/**
 * 
 */

class AHomeGameMode;

UCLASS()
class ABed : public ACommonInteractable
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	AHomeGameMode* HomeGameMode;

	bool bCanInteract = true;

	APlayerCameraManager* CameraManager;

private:
	virtual void InteractWithPlayer() override;

	UFUNCTION()
	void CameraFadeIn();

	UFUNCTION()
	void EndFade();
};
