#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class UCFModelAsset;

/**
 * Base AssetTypeActions for Catalyst model assets.
 * Feature plugins subclass and implement:
 *   - GetAssetClass()           (must derive from UCFModelAsset)
 *   - OpenModelEditor(...)      (spawn your toolkit/editor)
 *
 * They typically also pass a display name and type color via the ctor.
 */
class CATALYSTFOUNDATIONEDITOR_API FCFAssetTypeActions_Model : public FAssetTypeActions_Base
{
public:
	/** Provide the Content Browser display name and swatch color. */
	FCFAssetTypeActions_Model(FText InDisplayName, FColor InTypeColor);

	// ---------- FAssetTypeActions_Base ----------
	virtual FText   GetName() const override;
	virtual FColor  GetTypeColor() const override;
	virtual uint32  GetCategories() override;
	virtual UClass* GetSupportedClass() const override;
	virtual void    OpenAssetEditor(const TArray<UObject*>& InObjects,
	                                TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
	virtual FText   GetAssetDescription(const struct FAssetData& AssetData) const override;

protected:
	/** Your concrete asset class (must derive from UCFModelAsset). */
	virtual UClass* GetAssetClass() const = 0;

	/**
	 * Create and initialize your editor/toolkit for the asset.
	 * Typical impl: MakeShared<YourToolkit>()->Init(...).
	 */
	virtual void OpenModelEditor(UCFModelAsset* Asset,
	                             EToolkitMode::Type Mode,
	                             TSharedPtr<class IToolkitHost> EditWithinLevelEditor) = 0;

private:
	FText  DisplayName;
	FColor TypeColor;
};