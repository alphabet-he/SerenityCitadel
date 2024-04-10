// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingRobotCharacter.h"
#include "NinjaCharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "MyGameInstanceSubsystem.h"
#include "CommonFarmManager.h"
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetComponent.h>

AFarmingRobotCharacter::AFarmingRobotCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set up character 

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

	// Create target widget
	TargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Target Widget"));
	TargetWidget->SetupAttachment(RootComponent);


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));

	// can crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	
	// set ninja gravity type
	UNinjaCharacterMovementComponent* MovementComp = Cast<UNinjaCharacterMovementComponent>(GetMovementComponent());
	MovementComp->bAlignComponentToFloor = true;

	// set character type
	CharacterType = ECharacterType::FARMER;

}

void AFarmingRobotCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyGameInstanceSubsystem = Cast<UMyGameInstanceSubsystem>(
		GetWorld()->GetGameInstance()->GetSubsystem<UMyGameInstanceSubsystem>()
	);
	check(MyGameInstanceSubsystem);

	if (SeedPackage.Num() > 0) {
		auto It = SeedPackage.CreateConstIterator(); // Create a const iterator for the map
		HoldingSeed = It->Key; // Get the first key
	}

	FarmManager = Cast<ACommonFarmManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFarmManager::StaticClass()));
	check(FarmManager);
}

void AFarmingRobotCharacter::HandleExitFarm()
{
	MyGameInstanceSubsystem->SwitchToHome();
}

void AFarmingRobotCharacter::HandleSwitchProp()
{
	int ind = AvailableStates.IndexOfByKey(CurrFarmingState);
	ind++;
	if (ind == AvailableStates.Num()) {
		ind = 0;
	}
	
	CurrFarmingState = AvailableStates[ind];

	UpdateState();
}

void AFarmingRobotCharacter::HandleAnalyze()
{
	FarmManager->Analyze();
}

void AFarmingRobotCharacter::UpdateState()
{
	FString s = StaticEnum<EFarmingState>()->GetNameByValue(static_cast<int>(CurrFarmingState)).ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);

	FString Delimiter = TEXT("::");
	TArray<FString> Parsed;
	s.ParseIntoArray(Parsed, *Delimiter, true);

	FarmManager->UpdateState(Parsed[1]);
}

void AFarmingRobotCharacter::HandleInteract()
{
	if (CurrFarmingState == EFarmingState::IDLE) return;

	FarmManager->Operate(CurrFarmingState);
}




