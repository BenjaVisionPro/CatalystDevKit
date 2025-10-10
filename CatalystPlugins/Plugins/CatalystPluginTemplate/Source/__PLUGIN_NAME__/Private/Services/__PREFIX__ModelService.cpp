// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Services/__PREFIX__ModelService.h"
#include "UObject/UObjectIterator.h"

U__PREFIX__ModelService* U__PREFIX__ModelService::Instance()
{
	// Best-effort: return the first loaded instance (works in editor/PIE/tools).
	for (TObjectIterator<U__PREFIX__ModelService> It; It; ++It)
	{
		return *It;
	}
	return nullptr;
}