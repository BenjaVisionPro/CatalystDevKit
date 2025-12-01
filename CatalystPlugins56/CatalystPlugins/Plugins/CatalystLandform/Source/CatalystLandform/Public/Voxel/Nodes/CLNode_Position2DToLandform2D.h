// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelFloatBuffers.h"   // FVoxelVector2DBuffer, FVoxelFloatBuffer
#include "Buffer/VoxelDoubleBuffers.h"  // double buffers used internally
#include "CLNode_Position2DToLandform2D.generated.h"

/**
 * GetPosition2D (Float, cm) -> Landform2D (meters), plus Lat/Long (0..1) & Altitude (m).
 * Position is the XY (meters) tangent-plane used by noise.
 */
USTRUCT(Category = "Catalyst|Coords", DisplayName = "Position2D → Landform2D")
struct CATALYSTLANDFORM_API FCLNode_Position2DToLandform2D : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs
	VOXEL_INPUT_PIN(FVoxelVector2DBuffer, Position2D, nullptr,
		DisplayName("Position"),
		Tooltip("2D local position from GetPosition2D (Float); Z assumed 0 in local space."));

	VOXEL_INPUT_PIN(double, InnerRadiusM_Override, 0.0,
		DisplayName("Inner Radius (m) Override"),
		Tooltip("If > 0 with World Height > 0, overrides graph uniforms."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(double, WorldHeightM_Override, 0.0,
		DisplayName("World Height (m) Override"),
		Tooltip("If > 0 with Inner Radius > 0, overrides graph uniforms."),
		AdvancedDisplay);

	// Outputs
	VOXEL_OUTPUT_PIN(FVoxelVector2DBuffer, Position,
		DisplayName("Position"),
		Tooltip("Tangent-plane XY in meters (for use with Noise & spatial nodes)."));

	VOXEL_OUTPUT_PIN(FVoxelFloatBuffer, Latitude,
		DisplayName("Latitude (0..1)"),
		Tooltip("Normalized latitude-like coordinate (unitless)."),
		AdvancedDisplay);

	VOXEL_OUTPUT_PIN(FVoxelFloatBuffer, Longitude,
		DisplayName("Longitude (0..1)"),
		Tooltip("Normalized longitude-like coordinate (unitless)."),
		AdvancedDisplay);

	VOXEL_OUTPUT_PIN(FVoxelFloatBuffer, Altitude,
		DisplayName("Altitude (m)"),
		Tooltip("Altitude above inner radius in meters."),
		AdvancedDisplay);

	// FVoxelNode
	virtual void Compute(FVoxelGraphQuery Query) const override;
};