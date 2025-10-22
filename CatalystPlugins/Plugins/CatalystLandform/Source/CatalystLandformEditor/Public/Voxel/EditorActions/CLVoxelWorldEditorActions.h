#pragma once

#include "CoreMinimal.h"

class AVoxelWorld;
class UCLModelAsset;
class UCLVoxelWorldComponent;

namespace CLVoxelWorldEditorActions
{
	// Register/Unregister our LevelEditor actor context menu entry
	void RegisterMenus();
	void UnregisterMenus();

	// Handler that runs when the menu item is clicked
	void EnableCatalystLandform_OnSelectedWorlds();

	// Utility: ensure a CLVoxelWorldComponent exists on a world; optionally assign a model
	UCLVoxelWorldComponent* AddComponentIfMissing(AVoxelWorld& World, UCLModelAsset* OptionalModelAsset, bool bMarkDirty = true);
}