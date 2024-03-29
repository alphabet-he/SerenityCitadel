// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmingSubsystemController.generated.h"

UCLASS()
class FARMMODULE_API AFarmingSubsystemController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmingSubsystemController();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UMaterial*> GridTextures;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> BP_GridActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
