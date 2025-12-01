// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelFloatBuffers.h"
#include "CLNode_Landform2DToPosition2D.generated.h"

/**
 * Landform2D (meters) + S/T/R (m) -> Position2D (local cm, float)
 * Float wrapper that internally uses the double path for accuracy.
 */
USTRUCT(Category = "Catalyst|Coords", DisplayName = "Landform2D → Position2D")
struct CATALYSTLANDFORM_API FCLNode_Landform2DToPosition2D : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs
	VOXEL_INPUT_PIN(FVoxelVector2DBuffer, Landform2D, nullptr,
		DisplayName("Landform Position"),
		Tooltip("XY in meters on the selected coordinate space's tangent frame."));

	VOXEL_INPUT_PIN(FVoxelFloatBuffer, S, nullptr,
		DisplayName("Latitude (S)"),
		Tooltip("Latitude-like coordinate (unitless/normalized)."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(FVoxelFloatBuffer, T, nullptr,
		DisplayName("Longitude (T)"),
		Tooltip("Longitude-like coordinate (unitless/normalized)."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(FVoxelFloatBuffer, R_M, nullptr,
		DisplayName("Altitude (m)"),
		Tooltip("Altitude above inner radius, in meters."),
		AdvancedDisplay);

	// Output
	VOXEL_OUTPUT_PIN(FVoxelVector2DBuffer, Position2D,
		DisplayName("Position (local cm)"),
		Tooltip("Local XY in centimeters; Z is implicitly 0."));

	// FVoxelNode
	virtual void Compute(FVoxelGraphQuery Query) const override;
};