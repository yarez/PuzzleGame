// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LightsOut.h"
#include "LightsOutBlockGrid.h"
#include "LightsOutBlock.h"
#include "Components/TextRenderComponent.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ALightsOutBlock* Blocks[7][7];

ALightsOutBlockGrid::ALightsOutBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves Left: 35"), FText::AsNumber(0)));
	ScoreText->AttachTo(DummyRoot);

	// Set defaults
	Size = 5;
	BlockSpacing = 300.f;
}


void ALightsOutBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	//Initialize the block array
	for (int y = 0; y < 7; y++){
		for (int x = 0; x < 7; x++){
			Blocks[y][x] = NULL;
		}
	}

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++){
		const float YOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float XOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ALightsOutBlock* NewBlock = GetWorld()->SpawnActor<ALightsOutBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if(NewBlock != NULL)
		{
			NewBlock->OwningGrid = this;
		}

		Blocks[(BlockIndex % Size) + 1][(BlockIndex / Size) + 1] = NewBlock;

	}

	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			Blocks[i][j]->AdjacentBlocks[0] = Blocks[i + 1][j];
			Blocks[i][j]->AdjacentBlocks[1] = Blocks[i - 1][j];
			Blocks[i][j]->AdjacentBlocks[2] = Blocks[i][j + 1];
			Blocks[i][j]->AdjacentBlocks[3] = Blocks[i][j - 1];

		}
	}

}


void ALightsOutBlockGrid::SubScore()
{
	bool hasWon = true;

	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			if (Blocks[i][j]->bIsActive == false)
				hasWon = false;
		}
	}

	if (hasWon){
		ScoreText->SetText(LOCTEXT("ScoreFmt", "You Win!"));
		// decrement score
	}else if (Score > 0){
		Score--;
		ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves Left: {0}"), FText::AsNumber(Score)));
	}
	else{
		ScoreText->SetText(LOCTEXT("ScoreFmt", "You Lose!"));
	}
}

#undef LOCTEXT_NAMESPACE
