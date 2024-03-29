// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class GridType : uint8 {
	Count = 8 UMETA(DisplayName = "Count for the enum class"),
	SOIL = 0 UMETA(DisplayName = "SOIL"), // can become farmland, pit, and grass
	WATER = 1     UMETA(DisplayName = "WATER"),
	SAND = 2	UMETA(DisplayName = "SAND"),
	ROCK = 3	UMETA(DisplayName = "ROCK"),
	FARMLAND = 4  UMETA(DisplayName = "FARMLAND"), // can grow crops
	PIT = 5		UMETA(DisplayName = "PIT"), // can grow trees and flowers
	GRASS = 6	UMETA(DisplayName = "GRASS"), // can feed animals
	UNDEFINED = 7 UMETA(DisplayName = "UNDEFINED")
};

UENUM(BlueprintType)
enum class GridOperation : uint8 {
	CULTIVATE = 0 UMETA(ToolTip = "From Soil to Farmland"),
	DIG = 1 UMETA(ToolTip = "From Soil to Pit"),
	FILL = 2 UMETA(ToolTip = "From Water to Soil"),
	REMOVE = 3 UMETA(ToolTip = "From Rock to Other")
};

UENUM(BlueprintType)
enum class GroundEntityType : uint8 {
	PLANT = 0 UMETA(DisplayName = "PLANT"),
	CONSTRUCT = 1 UMETA(DisplayName = "CONSTRUCT")
};

UENUM(BlueprintType)
enum class PlantType : uint8 {
	CROP = 0 UMETA(DisplayName = "CROP"),
	TREE = 1 UMETA(DisplayName = "TREE"),
	FLOWER = 2 UMETA(DisplayName = "FLOWER")
};
