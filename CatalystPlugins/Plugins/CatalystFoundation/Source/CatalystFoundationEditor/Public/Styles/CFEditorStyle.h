#pragma once

#include "CoreMinimal.h"

/**
 * Foundation-wide editor StyleSet (icons, thumbnails, slate resources).
 * - Registers once on module startup; unregisters on shutdown.
 * - Looks for SVGs under <Plugin>/Resources/.
 * - Exposes ClassIcon.* and ClassThumbnail.* keys.
 */
class FCFEditorStyle
{
public:
	static void Register();
	static void Unregister();

	static const ISlateStyle& Get();
	static FName GetStyleSetName();

private:
	static TSharedPtr<class FSlateStyleSet> Style;
};