// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "LightsOutBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class ALightsOutBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	ALightsOutBlock();

	/** Are we currently active? */
	bool bIsActive=false;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* RedMaterial;


	/** Pointer to blue material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* GreenMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class ALightsOutBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	ALightsOutBlock* AdjacentBlocks[4];

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



