// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "FarmOperatingDesk.generated.h"


class UWidgetComponent;
class APlayerControllerTest;
class UUserWidget;

UCLASS()
class AFarmOperatingDesk : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmOperatingDesk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OperatingDeskMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* EtoInteractWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* OperatingWidget;

	APlayerControllerTest* PlayerController;

	bool OperatingWidgetVisible = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EnterPlayerInteractionBox() override;

	virtual void LeavePlayerInteractionBox() override;

	virtual void InteractWithPlayer() override;

};
