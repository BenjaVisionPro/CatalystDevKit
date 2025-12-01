#pragma once
#include "CoreMinimal.h"
class IBVCValidator { public: virtual ~IBVCValidator() = default; virtual bool Validate() const { return true; } };
