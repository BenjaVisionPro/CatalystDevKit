// ============================================
// Foundation: Model Service (per-plugin)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CFAbstractModelService.generated.h"

class UCFModelAsset;

/**
 * UCFAbstractModelService
 * -----------------------
 * One live model *asset* per plugin.
 * - Initializes once per GameInstance.
 * - Duplicates the seed asset to a transient instance, then optionally
 *   overlays Saved/<Plugin>/Model.json for quick iteration.
 * - Exposes typed helpers and static accessors to keep usage frictionless.
 */
UCLASS(Abstract)
class CATALYSTFOUNDATION_API UCFAbstractModelService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Stable access to the live model asset instance.
	const UCFModelAsset* GetModelAsset() const { return ModelAsset; }
	      UCFModelAsset* GetMutableModelAsset() { return ModelAsset; }

	// --- Static convenience: find a plugin service from anywhere (editor/game) ---
	template<typename TService>
	static const TService* Get()
	{
		if (!GEngine) return nullptr;

		// Try active worlds first (handles PIE + EditorWorld)
		for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
		{
			if (const UGameInstance* GI = Ctx.OwningGameInstance.Get())
			{
				if (const TService* Svc = GI->GetSubsystem<TService>())
				{
					return Svc;
				}
			}
		}

		// Fallback: engine subsystem (rarely needed)
		return GEngine->GetEngineSubsystem<TService>();
	}

	// Plugins must hardcode identity + seed.
	virtual FName GetPluginName() const PURE_VIRTUAL(UCFAbstractModelService::GetPluginName, return NAME_None;);
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const PURE_VIRTUAL(UCFAbstractModelService::GetSeedModelAsset, return nullptr;);

	// Boot/shutdown
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	// JSON first (if present), else seed defaults.
	bool LoadModel();

	// Duplicate seed to a transient instance we own.
	UCFModelAsset* InstantiateModelFromSeed();

protected:
	UPROPERTY(Transient)
	UCFModelAsset* ModelAsset = nullptr;
};