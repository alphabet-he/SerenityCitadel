// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerenityCitadelCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALMODULE_API APlayerCharacter : public ASerenityCitadelCharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
};
