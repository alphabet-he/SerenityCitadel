// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotMinimap.generated.h"

class USceneCaptureComponent2D;
class UBoxComponent;

UCLASS()
class HOMEMODULE_API ARobotMinimap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobotMinimap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MinimapMesh;

	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComp;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MinimapPawnStartPos;


};
