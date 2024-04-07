// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerControllerTest.h"
#include "MinimapPawn.generated.h"

struct FInputActionValue;
class UFloatingPawnMovement;
class UBoxComponent;

UCLASS()
class HOMEMODULE_API AMinimapPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinimapPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleMove(const FInputActionValue& Value);

	void SetForwardDirection(FVector v) {
		ForwardDirection = v;
	}

	void SetRightDirection(FVector v) {
		RightDirection = v;
	}

private:
	FVector ForwardDirection;
	FVector RightDirection;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* MovementComp;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;

};
