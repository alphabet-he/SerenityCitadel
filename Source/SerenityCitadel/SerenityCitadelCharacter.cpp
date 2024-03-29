// Fill out your copyright notice in the Description page of Project Settings.


#include "SerenityCitadelCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include <InteractionInterface.h>

// Sets default values
ASerenityCitadelCharacter::ASerenityCitadelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bEnableCameraLag = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// create trigger box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetRelativeScale3D(FVector(5.0, 5.0, 1.5));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));

	// can crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
}

void ASerenityCitadelCharacter::HandleMove(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("HandleMove"));
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		/* 
		* 
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		*
		*/

		// get forward vector
		FVector rot1 = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
		FVector rot2 = FRotationMatrix(GetCapsuleComponent()->GetComponentRotation()).GetUnitAxis(EAxis::Z);
		
		const FVector ForwardDirection = FVector::CrossProduct(rot1, rot2).GetSafeNormal(0.0001);

		// get right vector 
		FVector RightDirection = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASerenityCitadelCharacter::HandleLook(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("HandleLook"));
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASerenityCitadelCharacter::HandleJump()
{
	//UE_LOG(LogTemp, Warning, TEXT("HandleJump"));
	UnCrouch();
	Jump();
}

void ASerenityCitadelCharacter::HandleCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleCrouch"));
	if (bIsCrouched) UnCrouch();
	else Crouch();
}

void ASerenityCitadelCharacter::HandleInteract()
{
	if (InteractionInterface) {
		InteractionInterface->InteractWithPlayer();
	}
}

// Called when the game starts or when spawned
void ASerenityCitadelCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle InteractionBoxOverlapHandle;
	GetWorld()->GetTimerManager().SetTimer(InteractionBoxOverlapHandle, this, &ASerenityCitadelCharacter::CheckInteractionBox, CheckInteractionBoxFreq, true);
}

// Called every frame
void ASerenityCitadelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASerenityCitadelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASerenityCitadelCharacter::CheckInteractionBox()
{
	TArray<AActor*> OverlappingActors;

	InteractionBox->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() == 0) {
		if (InteractionInterface) {
			InteractionInterface->LeavePlayerInteractionBox();
			InteractionInterface = nullptr;
		}
		return;
	}

	AActor* InteractingActor = OverlappingActors[0];

	for (auto interactable : OverlappingActors) {
		if (GetDistanceTo(interactable) < GetDistanceTo(InteractingActor)) {
			InteractingActor = interactable;
		}
	}

	IInteractionInterface* interface = Cast<IInteractionInterface>(InteractingActor);

	if (interface) {
		if (InteractionInterface) {
			if (interface != InteractionInterface) {
				InteractionInterface->LeavePlayerInteractionBox();
			}
			else {
				return;
			}
		}
		InteractionInterface = interface;
		interface->EnterPlayerInteractionBox();
		
		//interface->ShowInteractionWidget();
	}
	
}

