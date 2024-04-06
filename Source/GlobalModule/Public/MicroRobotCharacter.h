// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerenityCitadelCharacter.h"
#include "MicroRobotCharacter.generated.h"

/**
 * 
 */

UCLASS()
class GLOBALMODULE_API AMicroRobotCharacter : public ASerenityCitadelCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMicroRobotCharacter(const FObjectInitializer& ObjectInitializer);

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
