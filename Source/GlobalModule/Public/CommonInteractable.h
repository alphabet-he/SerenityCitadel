// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "CommonInteractable.generated.h"


class UWidgetComponent;
class APlayerControllerTest;

UCLASS()
class GLOBALMODULE_API ACommonInteractable : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommonInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* InteractableMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* EToInteractWidget;

public:

	virtual void EnterPlayerInteractionBox() override;

	virtual void LeavePlayerInteractionBox() override;

};
