// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "RobotMinimap.generated.h"

class USceneCaptureComponent2D;
class UBoxComponent;
class AHomeGameMode;

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

	UPROPERTY(EditAnywhere)
	UBoxComponent* TargetPos;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ForwardDirection;

private:
	AHomeGameMode* HomeGameMode;

public:
	FVector GetPawnSpawnPos() {
		return MinimapPawnStartPos->GetComponentLocation();
	}

	FVector GetForwardDirection() {
		return ForwardDirection->GetForwardVector();
	}

	FVector GetRightDirection() {
		return ForwardDirection->GetRightVector();
	}

private:
	UFUNCTION()
	void ArriveAtTarget(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void LeaveTarget(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
