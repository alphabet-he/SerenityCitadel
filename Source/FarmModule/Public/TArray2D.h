// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

template <typename ElementType>
class TArray2D 
{
private:
	int SizeRow = -1; // row
	int SizeColumn = -1; // column
	TArray<ElementType> InnerArray;

public:
	void Init(int Row, int Column, const ElementType& Element) {
		SizeRow = Row;
		SizeColumn = Column;
		InnerArray.Init(Element, Row * Column);
	}

	FORCEINLINE ElementType& GetElement(const int Row, const int Column) {
		return InnerArray[(Row * SizeColumn) + Column];
	}

	FORCEINLINE void SetElement(const int Row, const int Column, const ElementType& i) {
		InnerArray[(Row * SizeColumn) + Column] = i;
	}

	FORCEINLINE int GetRow() { return SizeRow; }
	FORCEINLINE int GetColumn() { return SizeColumn; }

	FORCEINLINE bool IsEmpty() { return (SizeRow == -1); }

	FORCEINLINE ElementType* GetElementUp(const int x, const int y) {
		if (y <= 0) return nullptr;
		else return &GetElement(x, y - 1);
	}

	FORCEINLINE ElementType* GetElementDown(const int x, const int y) {
		if (y >= SizeColumn - 1) return nullptr;
		else return &GetElement(x, y + 1);
	}

	FORCEINLINE ElementType* GetElementLeft(const int x, const int y) {
		if (x <= 0) return nullptr;
		else return &GetElement(x - 1, y);
	}

	FORCEINLINE ElementType* GetElementRight(const int x, const int y) {
		if (x >= SizeRow - 1) return nullptr;
		else return &GetElement(x + 1, y);
	}

	void print() {
		for (int i = 0; i < SizeRow; i++) {
			for (int j = 0; j < SizeColumn; j++) {

			}
		}
	}
};
