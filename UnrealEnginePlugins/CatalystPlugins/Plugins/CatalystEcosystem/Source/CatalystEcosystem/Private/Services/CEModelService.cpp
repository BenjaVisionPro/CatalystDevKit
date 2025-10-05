// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Services/CEModelService.h"
#include "UObject/UObjectIterator.h"

UCEModelService* UCEModelService::Instance()
{
	// Best-effort: return the first loaded instance (works in editor/PIE/tools).
	for (TObjectIterator<UCEModelService> It; It; ++It)
	{
		return *It;
	}
	return nullptr;
}