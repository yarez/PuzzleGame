// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LightsOut.h"
#include "LightsOutBlock.h"
#include "LightsOutBlockGrid.h"

ALightsOutBlock::ALightsOutBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/Green.Green"))
			, RedMaterial(TEXT("/Game/Puzzle/Meshes/Red.Red"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Save a pointer to the orange material
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();

	int random = rand() % 2;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	if (random == 1){
		bIsActive = true;
		BlockMesh->SetMaterial(0, RedMaterial);
	}else if (random == 0){
		bIsActive = false;
		BlockMesh->SetMaterial(0, GreenMaterial);
	}	

	BlockMesh->AttachTo(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ALightsOutBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ALightsOutBlock::OnFingerPressedBlock);


}

void ALightsOutBlock::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	// Check we are not already active
	if(!bIsActive)
	{
		bIsActive = true;
		// Change material
		BlockMesh->SetMaterial(0, RedMaterial);
		// Tell the Grid
		if(OwningGrid != NULL)
		{
			OwningGrid->SubScore();
		}
	}
	else{
		bIsActive = false;
		BlockMesh->SetMaterial(0,GreenMaterial);
		// Tell the Grid
		if (OwningGrid != NULL)
		{
			OwningGrid->SubScore();
		}
	}

	for (int i = 0; i < 4; i++){
		// Check we are not already active
		if (AdjacentBlocks[i] != NULL && !(AdjacentBlocks[i]->bIsActive))
		{
			AdjacentBlocks[i]->bIsActive = true;
			AdjacentBlocks[i]->BlockMesh->SetMaterial(0, RedMaterial);
			
		}else if(AdjacentBlocks[i] != NULL && AdjacentBlocks[i]->bIsActive){
			AdjacentBlocks[i]->bIsActive = false;
			AdjacentBlocks[i]->BlockMesh->SetMaterial(0, GreenMaterial);
		}
	}
	
}


void ALightsOutBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	BlockClicked(TouchedComponent);
}
