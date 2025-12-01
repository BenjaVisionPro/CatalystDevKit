// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "CLNode_Position2DToLandform2D_Double.generated.h"

/**
 * GetPosition2D (Double) -> Landform2D (meters), with STR (m) as advanced outputs.
 * Inputs:
 *   - Position 2D (Local cm): 2D local position from GetPosition2D (Double); Z assumed 0 in local space.
 *   - Inner/World overrides: If both > 0, will override uniforms.
 * Outputs:
 *   - Landform 2D (m): Tangent-plane XY in meters (X=East, Y=North) for 2D noise.
 *   - S,T,R (m): Geodesic coordinates in meters (advanced).
 */
USTRUCT(Category = "Catalyst|Coords", DisplayName = "Position2D → Landform2D (double)")
struct CATALYSTLANDFORM_API FCLNode_Position2DToLandform2D_Double : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs
	VOXEL_INPUT_PIN(FVoxelDoubleVector2DBuffer, Position2D, nullptr,
		DisplayName("Position"),
		Tooltip("2D local position from GetPosition2D (Double); Z assumed 0 in local space."));

	VOXEL_INPUT_PIN(double, InnerRadiusM_Override, 0.0,
		DisplayName("Inner Radius (m) Override"),
		Tooltip("Optional. If > 0 with World Height > 0, overrides uniforms."),
		AdvancedDisplay);

	VOXEL_INPUT_PIN(double, WorldHeightM_Override, 0.0,
		DisplayName("World Height (m) Override"),
		Tooltip("Optional. If > 0 with Inner Radius > 0, overrides uniforms."),
		AdvancedDisplay);

	// Outputs
	VOXEL_OUTPUT_PIN(FVoxelDoubleVector2DBuffer, Landform2D,
		DisplayName("Landform Position"),
		Tooltip("Tangent-plane XY in meters (X=East, Y=North)."));

	// Advanced outputs (S T R in meters)
	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, S,
		DisplayName("S"),
		Tooltip("Longitude-like coordinate (unitless 0..1 typical)."),
		AdvancedDisplay);

	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, T,
		DisplayName("T"),
		Tooltip("Latitude-like coordinate (unitless 0..1 typical)."),
		AdvancedDisplay);

	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, R_M,
		DisplayName("(m) R"),
		Tooltip("Altitude above inner radius, in meters."),
		AdvancedDisplay);

	// FVoxelNode
	virtual void Compute(FVoxelGraphQuery Query) const override;
};