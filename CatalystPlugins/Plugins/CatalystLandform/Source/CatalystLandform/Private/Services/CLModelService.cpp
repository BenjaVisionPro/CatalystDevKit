// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Services/CLModelService.h"
#include "UObject/UObjectIterator.h"

UCLModelService* UCLModelService::Instance()
{
	// Best-effort: return the first loaded instance (works in editor/PIE/tools).
	for (TObjectIterator<UCLModelService> It; It; ++It)
	{
		return *It;
	}
	return nullptr;
}