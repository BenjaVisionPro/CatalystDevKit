// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "CLNode_Landform2DToPosition2D_Double.generated.h"

/**
 * Landform2D (meters) + S/T/R (m) -> Position2D (local cm, double)
 * Intended as the reverse of Position2D → Landform2D (double).
 */
USTRUCT(Category = "Catalyst|Coords", DisplayName = "Landform2D → Position2D (double)")
struct CATALYSTLANDFORM_API FCLNode_Landform2DToPosition2D_Double : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs
	VOXEL_INPUT_PIN(FVoxelDoubleVector2DBuffer, Landform2D, nullptr,
		DisplayName("Landform Position (m)"),
		Tooltip("XY in meters on the selected coordinate space's tangent frame."));

	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, S, nullptr,
		DisplayName("Latitude (S)"),
		Tooltip("Latitude-like coordinate (unitless/normalized)."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, T, nullptr,
		DisplayName("Longitude (T)"),
		Tooltip("Longitude-like coordinate (unitless/normalized)."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, R_M, nullptr,
		DisplayName("Altitude (m)"),
		Tooltip("Altitude above inner radius, in meters."),
		AdvancedDisplay);

	// Output
	VOXEL_OUTPUT_PIN(FVoxelDoubleVector2DBuffer, Position2D,
		DisplayName("Position (local cm)"),
		Tooltip("Local XY in centimeters; Z is implicitly 0."));

	// FVoxelNode
	virtual void Compute(FVoxelGraphQuery Query) const override;
};