// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "Teleporter.generated.h"


class UWidgetComponent;
class APlayerControllerTest;

UCLASS()
class ATeleporter : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TeleporterMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionWidget;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* TeleporterWidget;

	APlayerControllerTest* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EnterPlayerInteractionBox() override;

	virtual void LeavePlayerInteractionBox() override;

	virtual void InteractWithPlayer() override;
		
};
