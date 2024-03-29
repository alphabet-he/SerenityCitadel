// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSubsystem.h"
#include "FarmModuleEnums.h"
#include "FarmingGrid.h"
#include <random>
#include <OperatingWidget.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UFarmingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// soil transition mappings
	FGridTransitionWrapper SoilWrapper;
	SoilWrapper._GridType = GridType::SOIL;
	SoilWrapper.OperationNum = 2;
	SoilWrapper.OperationMapping.Add(GridOperation::CULTIVATE, GridType::FARMLAND);
	SoilWrapper.OperationMapping.Add(GridOperation::DIG, GridType::PIT);

	// water transition mappings
	FGridTransitionWrapper WaterWrapper;
	WaterWrapper._GridType = GridType::WATER;
	WaterWrapper.OperationNum = 1;
	WaterWrapper.OperationMapping.Add(GridOperation::FILL, GridType::SOIL);

	// rock transition mappings
	FGridTransitionWrapper RockWrapper;
	RockWrapper._GridType = GridType::ROCK;
	RockWrapper.OperationNum = 1;
	RockWrapper.OperationMapping.Add(GridOperation::REMOVE, GridType::UNDEFINED);

	// grid transition mappings
	GridTransitionMapping.Add(GridType::SOIL, SoilWrapper);
	GridTransitionMapping.Add(GridType::WATER, WaterWrapper);
	GridTransitionMapping.Add(GridType::ROCK, RockWrapper);
}



void UFarmingSubsystem::SpawnGrid(const FVector p1, const FVector p2,
	FNoiseMapParams heightMapParams, FNoiseMapParams moistureMapParams, FNoiseMapParams temperatureMapParams,
	float sandMoistureThreshold, float sandTemperatureThreshold,
	float waterMoistureThreshold, float waterHeightThreshold,
	float rockPercent)
{
	//assert(BP_GridActor == AFarmingGrid::StaticClass());
	check(p1.Z == p2.Z); // horizontal

	int gridLength = GridUnitLength * GridScale;

	check(fmod((p1.X - p2.X), gridLength) == 0); // can fit in
	check(fmod((p1.Y - p2.Y), gridLength) == 0);

	float x_min = std::min(p1.X, p2.X);
	float x_max = std::max(p1.X, p2.X);
	float y_min = std::min(p1.Y, p2.Y);
	float y_max = std::max(p1.Y, p2.Y);

	int x_size = (x_max - x_min) / gridLength;
	int y_size = (y_max - y_min) / gridLength;

	GridMap.Init(x_size, y_size, -1);
	GridPtrs.Init(x_size, y_size, nullptr);

	// generate noise map
	TArray2D<float> heightMap = GeneratePerlinNoiseMap(x_size, y_size, heightMapParams);
	TArray2D<float> moistureMap = GeneratePerlinNoiseMap(x_size, y_size, moistureMapParams);
	TArray2D<float> temperatureMap = GeneratePerlinNoiseMap(x_size, y_size, temperatureMapParams);

	int x_count = -1;

	// generate grids based on noise map
	for (float x = x_max - gridLength / 2; x >= x_min + gridLength / 2; x = x - gridLength)
	{
		x_count++;
		int y_count = -1;

		for (float y = y_min + gridLength / 2; y <= y_max - gridLength / 2; y = y + gridLength)
		{
			y_count++;

			FVector SpawnLocation = FVector(x, y, p1.Z + heightMap.GetElement(x_count, y_count));
			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters spawnParams;
			AFarmingGrid* NewFarmingGrid = GetWorld()->SpawnActor<AFarmingGrid>(BP_GridActor, SpawnLocation, SpawnRotation, spawnParams);
			if (NewFarmingGrid) {
				if (moistureMap.GetElement(x_count, y_count) < sandMoistureThreshold && temperatureMap.GetElement(x_count, y_count) > sandTemperatureThreshold) {
					GridMap.SetElement(x_count, y_count, static_cast<int>(GridType::SAND));
					NewFarmingGrid->setGridType(GridType::SAND);
				}
				else if (moistureMap.GetElement(x_count, y_count) > waterMoistureThreshold && heightMap.GetElement(x_count, y_count) < waterHeightThreshold) {
					GridMap.SetElement(x_count, y_count, static_cast<int>(GridType::WATER));
					NewFarmingGrid->setGridType(GridType::WATER);
				}
				else {
					GridMap.SetElement(x_count, y_count, static_cast<int>(GridType::SOIL));
					NewFarmingGrid->setGridType(GridType::SOIL);
				}
				GridPtrs.SetElement(x_count, y_count, NewFarmingGrid);
				NewFarmingGrid->UpdateGrid();
			}
		}
	}

	if (rockPercent > 0) {
		FRandomStream Stream(FMath::Rand());

		int rockNum = (float)x_size * (float)y_size * rockPercent;

		for (int i = 0; i < rockNum; i++) {
			int rowInd = FMath::RandRange(0, x_size - 1);
			int columnInd = FMath::RandRange(0, y_size - 1);
			if (GridMap.GetElement(rowInd, columnInd) != static_cast<int>(GridType::ROCK)) {
				GridMap.SetElement(rowInd, columnInd, static_cast<int>(GridType::ROCK));
				GridPtrs.GetElement(rowInd, columnInd)->setGridType(GridType::ROCK);
				GridPtrs.GetElement(rowInd, columnInd)->UpdateGrid();
			}
		}
	}
	

	

	/*
	GenerateSandArea(
		5, 7, 0.15f, 0.15f,
		0.25f, 0.25f
	);

	TArray<FVector> Points = GenerateWanderingLine(FVector{ 0, 0, 30 }, FVector{ 1500, 2000, 30 }, 100, 0.1f, 100.0f);

	UWorld* World = GetWorld();
	if (World && Points.Num() > 1)
	{
		for (int32 i = 0; i < Points.Num() - 1; ++i)
		{
			DrawDebugLine(World, Points[i], Points[i + 1], FColor::Red, false, 300.0f, 0, 2.0f);
		}
	}

	//GenerateRiver(
	//	10, 40,
	//	30, 6, 0.1f, 0.1f, 5,
	//	150,
	//	0.3f,
	//	3, 1, 0.0f, 0.0f,
	//	1, 1, 0.0f, 0.0f,
	//	0.5f,
	//	4, 3, 0.15f, 0.15f
	//);

	*/

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Generating done"));
	
}

TArray2D<float> UFarmingSubsystem::GeneratePerlinNoiseMap(int rowSize, int columnSize, FNoiseMapParams noiseMapParams) {
	if (noiseMapParams.inputRange.Num() != 2) {
		UE_LOG(LogTemp, Warning, TEXT("Noise map params wrong! Expected 2 input range - received %i"), noiseMapParams.inputRange.Num());
		TArray2D<float> noiseMap;
		return noiseMap;
	}

	TArray2D<float> noiseMap;
	noiseMap.Init(rowSize, columnSize, 0);

	// determine seed
	float seed = 0;
	if (noiseMapParams.bUseSeed) {
		seed = noiseMapParams.seed;
	}
	else {
		FRandomStream Stream(FMath::Rand());
		seed = FMath::Rand();
	}

	// determine multiplier
	float multiplier = 1;
	if (noiseMapParams.bMultiplier) {
		multiplier = noiseMapParams.multiplier;
	}
	
	// generate noise values
	float maxVal = INT_MIN;
	float minVal = INT_MAX;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < columnSize; j++) {

			float rowSample = (float)i / rowSize * noiseMapParams.inputRange[0] + seed;
			float columnSample = (float)j / columnSize * noiseMapParams.inputRange[1] + seed;
			
			float value = FMath::PerlinNoise2D(FVector2D{ columnSample, rowSample }) * multiplier;
			if (value > maxVal) maxVal = value;
			if (value < minVal) minVal = value;
			noiseMap.SetElement(i, j, value);
		}
	}

	// scale noise map
	if (noiseMapParams.bScale && maxVal != minVal) {
		for (int i = 0; i < rowSize; i++) {
			for (int j = 0; j < columnSize; j++) {
				float scaledVal = noiseMap.GetElement(i, j);
				scaledVal = (scaledVal - minVal) / (maxVal - minVal) * (noiseMapParams.max - noiseMapParams.min) + noiseMapParams.min;
				noiseMap.SetElement(i, j, scaledVal);
			}
		}
	}

	return noiseMap;
}

void UFarmingSubsystem::GenerateRiver(
	int riverExpandMargin, int lakeExpandMargin,
	float exptLength, int lengthAttemptNum, float lengthIncProb, float lengthDecProb, float lengthDevRange,
	int randomPairAttempNum,
	float wanderProb,
	int exptMaxWidth, int maxWidthAttemptNum, float maxWidthIncProb, float maxWidthDecProb,
	int exptMinWidth, int minWidthAttemptNum, float minWidthIncProb, float minWidthDecProb,
	float lakeProb,
	int exptLakeRadius, int lakeRadiusAttemptNum, float lakeRadiusIncProb, float lakeRadiusDecProb) 
{
	// Check GridMap is initialized
	check(!GridMap.IsEmpty());

	// create a map that is larger than the actual grid map
	int x_size = GridMap.GetColumn();
	int y_size = GridMap.GetRow();
	TArray2D<bool> RiverMap;
	int river_x_size = x_size + 2 * riverExpandMargin;
	int river_y_size = y_size + 2 * riverExpandMargin;
	RiverMap.Init(river_y_size, river_x_size, false);


	// decide the river length based on the length distribution
	float targetLength = GetValue(exptLength, lengthAttemptNum, lengthIncProb, lengthDecProb);

	// get target pair
	TTuple<FCoordinate2D, FCoordinate2D> targetPair;

	// if within the size
	if (targetLength <= river_x_size && targetLength <= river_y_size) {
		float minDev = INT_MAX;
		while (true) {
			for (int i = 0; i < randomPairAttempNum; i++) {
				FCoordinate2D p1 = FCoordinate2D(FMath::RandRange(0, river_x_size - 1), FMath::RandRange(0, river_y_size - 1));
				FCoordinate2D p2 = FCoordinate2D(FMath::RandRange(0, river_x_size - 1), FMath::RandRange(0, river_y_size - 1));
				float dist = GetDist(p1, p2);
				if (abs(dist - targetLength) < minDev) {
					targetPair = TTuple<FCoordinate2D, FCoordinate2D>(p1, p2);
					minDev = abs(dist - targetLength);
				}
			}
			if (minDev <= lengthDevRange) {
				break;
			}
		}
	}

	// exceed the size
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("River exceed size"));
		// select on edge
	}
	

	// decide whether there will be lake
	bool lakePresent = false;
	float r = FMath::FRandRange(0.0f, 1.0f);
	if (r < lakeProb) {
		lakePresent = true;
	}

	// decide min and max width
	int maxWidth = std::max(1, (int)GetValue(exptMaxWidth, maxWidthAttemptNum, maxWidthIncProb, maxWidthDecProb));
	int minWidth = std::max(1, (int)GetValue(exptMinWidth, minWidthAttemptNum, minWidthIncProb, minWidthDecProb));

	// generate the wandering river road

	// calculate the angle
	float delta_Row = targetPair.Get<0>().Row - targetPair.Get<1>().Row;
	float delta_Column = targetPair.Get<0>().Column - targetPair.Get<1>().Column;
	
	float theta = atan2f(delta_Row, delta_Column);
	if (theta < 0) {
		theta += PI / 2;
	}

	TArray<int> x;
	TArray<int> y;

	for (float i = -200; i < 200; i = i + 0.5) {
		int _x = round(i * cos(theta) - sin(i) * sin(theta));
		int _y = round(i * sin(theta) + sin(i) * cos(theta));
		x.Add(_x);
		y.Add(_y);
	}

	FString FilePath_x = FPaths::ProjectDir() / TEXT("DebugCSV/river_x.csv");
	FString FilePath_y = FPaths::ProjectDir() / TEXT("DebugCSV/river_y.csv");
	SaveArrayToCSV(x, FilePath_x);
	SaveArrayToCSV(y, FilePath_y);

	for (int i = 0; i < x.Num(); i++) {
		if (x[i] >= 0 && x[i] < river_x_size && y[i] >= 0 && y[i] < river_y_size) {
			RiverMap.SetElement(y[i], x[i], true);
		}
	}

	// transfer river map to grid map
	for (int i = riverExpandMargin; i < river_y_size - riverExpandMargin; i++) {
		for (int j = riverExpandMargin; j < river_x_size - riverExpandMargin; j++) {
			if (RiverMap.GetElement(i, j)) {
				GridMap.SetElement(i - riverExpandMargin, j - riverExpandMargin, static_cast<int>(GridType::WATER));
			}
			
		}
	}

	// update grid map
	UpdateGridsFromTypes(TArray<GridType>{GridType::SOIL, GridType::SAND});

}

TArray<FVector> UFarmingSubsystem::GenerateWanderingLine(const FVector& Start, const FVector& End, int32 NumPoints, float NoiseScale, float MaxOffset)
{
	TArray<FVector> Points;

	// Direction and length from start to end
	FVector Direction = End - Start;
	float Length = Direction.Size();
	Direction.Normalize();

	// Perpendicular direction to the main direction
	FVector Perpendicular(-Direction.Y, Direction.X, 0.0f);

	for (int32 i = 0; i <= NumPoints; ++i)
	{
		float T = (float)i / (float)NumPoints;
		FVector PointOnLine = FMath::Lerp(Start, End, T);

		// Applying noise to get offset
		float NoiseValue = FMath::PerlinNoise1D(i * NoiseScale) * MaxOffset;

		// Wandering point
		FVector WanderingPoint = PointOnLine + Perpendicular * NoiseValue;
		Points.Add(WanderingPoint);
	}

	return Points;
}

void UFarmingSubsystem::GenerateSandArea(
	int exptRadius, int radiusAttemptNum, float radiusIncProb, float radiusDecProb,
	float boundaryIncProb, float boundaryDecProb
	) {

	// Check GridMap is initialized
	check(!GridMap.IsEmpty());

	// get x,y_size
	int x_size = GridMap.GetRow();
	int y_size = GridMap.GetColumn();

	// random seed
	FRandomStream Stream(FMath::Rand());

	// select a random position for sand
	int rand_x = Stream.RandRange(0, x_size);
	int rand_y = Stream.RandRange(0, x_size);

	// decide the radius of the sand area
	int radius = GetValue(exptRadius, radiusAttemptNum, radiusIncProb, radiusDecProb);

	// set all grids in the radius as sand
	int x_sand_min = std::max(0, rand_x - radius);
	int x_sand_max = std::min(x_size, rand_x + radius);
	int y_sand_min = std::max(0, rand_y - radius);
	int y_sand_max = std::min(y_size, rand_y + radius);

	for (int i = x_sand_min; i <= x_sand_max; i++) {
		for (int j = y_sand_min; j <= y_sand_max; j++) {
			GridMap.SetElement(i, j, static_cast<int>(GridType::SAND));
		}
	}
	
	
	// randomly change the boundary of sand

	// up boundary
	for (int i = x_sand_min; i < x_sand_max; i++) {
		ModifyEdgePoint(i, y_sand_min, boundaryIncProb, boundaryDecProb);
	}
	// right boundary
	for (int i = y_sand_min; i < y_sand_max; i++) {
		ModifyEdgePoint(x_sand_max, i, boundaryIncProb, boundaryDecProb);
	}
	// bottom boundary
	for (int i = x_sand_min; i <= x_sand_max; i++) {
		ModifyEdgePoint(i, y_sand_max, boundaryIncProb, boundaryDecProb);
	}
	// left boundary
	for (int i = y_sand_min + 1; i < y_sand_max; i++) {
		ModifyEdgePoint(x_sand_min, i, boundaryIncProb, boundaryDecProb);
	}

	UpdateGridsFromTypes(TArray<GridType>{GridType::SOIL});

}

void UFarmingSubsystem::ModifyEdgePoint(int x, int y, float boundaryIncProb, float boundaryDecProb) {
	
	FRandomStream Stream(FMath::Rand());
	float r = Stream.FRandRange(0.0f, 1.0f);

	// test whether need to expand
	TQueue<FCoordinate2D> toExpand;
	if (r < boundaryIncProb) {
		QueueSurrGridOfType(x, y, GridType::SOIL, toExpand);
	}
	// use BFS-like search to roughly look at its surrounding points
	while (!toExpand.IsEmpty())
	{
		FCoordinate2D currTuple;
		toExpand.Dequeue(currTuple);

		// if the element is already processed
		if (GridMap.GetElement(currTuple.Row, currTuple.Column) == static_cast<int>(GridType::SAND))
			continue;
		float r_curr = Stream.FRandRange(0.0f, 1.0f);
		if (r_curr < boundaryIncProb) {
			GridMap.SetElement(currTuple.Row, currTuple.Column, static_cast<int>(GridType::SAND));
			QueueSurrGridOfType(currTuple.Row, currTuple.Column, GridType::SOIL, toExpand);
		}
	}


	// test whether need to shrink
	TQueue<FCoordinate2D> toShrink;
	if (r > 1 - boundaryDecProb) {
		QueueSurrGridOfType(x, y, GridType::SAND, toShrink);
		GridMap.SetElement(x, y, static_cast<int>(GridType::SOIL));
	}
	// use BFS-like search to roughly look at its surrounding points
	while (!toShrink.IsEmpty())
	{
		FCoordinate2D currTuple;
		toShrink.Dequeue(currTuple);

		// if the element is already processed
		if (GridMap.GetElement(currTuple.Row, currTuple.Column) == static_cast<int>(GridType::SOIL))
			continue;
		float r_curr = Stream.FRandRange(0.0f, 1.0f);
		if (r_curr > 1 - boundaryDecProb) {
			
			GridMap.SetElement(currTuple.Row, currTuple.Column, static_cast<int>(GridType::SOIL));
			QueueSurrGridOfType(currTuple.Row, currTuple.Column, GridType::SAND, toShrink);
		}
	}
}


void UFarmingSubsystem::QueueSurrGridOfType(int x, int y, GridType type, TQueue<FCoordinate2D>& queue) {
	if (GridMap.GetElementUp(x, y)) {
		if (*(GridMap.GetElementUp(x, y)) == static_cast<int>(type)) {
			queue.Enqueue(FCoordinate2D(x, y - 1));
		}
	}
		
	if (GridMap.GetElementDown(x, y)) {
		if (*(GridMap.GetElementDown(x, y)) == static_cast<int>(type)) {
			queue.Enqueue(FCoordinate2D(x, y + 1));
		}
	}
		
	if (GridMap.GetElementLeft(x, y)) {
		if (*(GridMap.GetElementLeft(x, y)) == static_cast<int>(type)) {
			queue.Enqueue(FCoordinate2D(x - 1, y));
		}

	}
		
	if (GridMap.GetElementRight(x, y)) {
		if (*(GridMap.GetElementRight(x, y)) == static_cast<int>(type)) {
			queue.Enqueue(FCoordinate2D(x + 1, y));
		}
	}

}

void UFarmingSubsystem::UpdateGridsFromTypes(TArray<GridType> types) {
	TArray<int> typeInts;
	for (GridType type : types) {
		typeInts.AddUnique(static_cast<int>(type));
	}

	// iterate through the grid map
	for (int i = 0; i < GridMap.GetRow(); i++) {
		for (int j = 0; j < GridMap.GetColumn(); j++) {
			if (typeInts.Contains(GridMap.GetElement(i, j))) {
				continue;
			}
			else {
				GridPtrs.GetElement(i, j)->setGridType(
					static_cast<GridType>(GridMap.GetElement(i, j))
				);
				GridPtrs.GetElement(i, j)->UpdateGrid();
			}
		}
	}
}


void UFarmingSubsystem::SpawnGridRandom(const FVector p1, const FVector p2)
{
	//check(BP_GridActor == AFarmingGrid::StaticClass());
	check(p1.Z == p2.Z); // horizontal

	int gridLength = GridUnitLength * GridScale;

	check(fmod((p1.X - p2.X), gridLength) == 0); // can fit in
	check(fmod((p1.Y - p2.Y), gridLength) == 0);

	float x_min = std::min(p1.X, p2.X);
	float x_max = std::max(p1.X, p2.X);
	float y_min = std::min(p1.Y, p2.Y);
	float y_max = std::max(p1.Y, p2.Y);

	int x_size = (x_max - x_min) / gridLength;
	int y_size = (y_max - y_min) / gridLength;

	UE_LOG(LogTemp, Warning, TEXT("x_size: %i"), x_size );

	GridMap.Init(y_size, x_size, -1);
	GridPtrs.Init(y_size, x_size, nullptr);

	int x_count = -1;

	for (float x = x_min + gridLength / 2; x <= x_max - gridLength / 2; x = x + gridLength)
	{
		x_count++;
		int y_count = -1;
		for (float y = y_min + gridLength / 2; y <= y_max - gridLength / 2; y = y + gridLength)
		{
			y_count++;
			FVector SpawnLocation = FVector(x, y, p1.Z);
			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters spawnParams;
			AFarmingGrid* NewFarmingGrid = GetWorld()->SpawnActor<AFarmingGrid>(BP_GridActor, SpawnLocation, SpawnRotation, spawnParams);
			if (NewFarmingGrid) {
			// do things to the newly spawned grid

				int r = (rand() % static_cast<int>(GridType::Count)); // random grid type
				GridMap.SetElement(r, x_count, y_count);
				NewFarmingGrid->setGridType(static_cast<GridType>(r));
				NewFarmingGrid->UpdateGrid();
			}
		}
	}
}

void UFarmingSubsystem::ChangeGrid(FCoordinate2D gridCoordinate, GridType newType)
{
	GridMap.SetElement(gridCoordinate.Row, gridCoordinate.Column, static_cast<int>(newType));
	GridPtrs.GetElement(gridCoordinate.Row, gridCoordinate.Column)->setGridType(newType);
	GridPtrs.GetElement(gridCoordinate.Row, gridCoordinate.Column)->UpdateGrid();
	if (!OperatingWidget) {
		TArray<UUserWidget*> Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UOperatingWidget::StaticClass(), true);

		OperatingWidget = Cast<UOperatingWidget>(Widgets[0]);
	}
	if (OperatingWidget) {
		OperatingWidget->UpdateGridButtonColor(gridCoordinate.Row, gridCoordinate.Column);
	}
	
}

void UFarmingSubsystem::SaveArrayToCSV(const TArray<int32>& MyArray, const FString& FilePath)
{
	TArray<FString> LinesToSave;
	for (int32 Element : MyArray)
	{
		FString Line = FString::Printf(TEXT("%d"), Element);
		LinesToSave.Add(Line);
	}

	FFileHelper::SaveStringArrayToFile(LinesToSave, *FilePath);
}





