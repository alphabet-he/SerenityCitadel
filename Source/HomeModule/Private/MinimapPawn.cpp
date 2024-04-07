// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"

// Sets default values
AMinimapPawn::AMinimapPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere Collider"));

	RootComponent = BoxCollider;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Mesh"));
	PawnMesh->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
}

// Called when the game starts or when spawned
void AMinimapPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMinimapPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMinimapPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMinimapPawn::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//if (MovementVector.Y != 0) {
	//	AddActorLocalOffset(ForwardDirection * MovementVector.Y);
	//}

	//if (MovementVector.X != 0) {
	//	AddActorLocalOffset(RightDirection * MovementVector.X);
	//}

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

