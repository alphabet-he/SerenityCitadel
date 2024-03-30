// Fill out your copyright notice in the Description page of Project Settings.


#include "MicroRobotCharacter.h"
#include "NinjaCharacterMovementComponent.h"

AMicroRobotCharacter::AMicroRobotCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set ninja gravity type
	UNinjaCharacterMovementComponent* MovementComp = Cast<UNinjaCharacterMovementComponent>(GetMovementComponent());
	MovementComp->bAlignComponentToFloor = true;
}




