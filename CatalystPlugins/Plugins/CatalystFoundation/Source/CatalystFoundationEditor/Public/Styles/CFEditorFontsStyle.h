#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**
 * Catalyst:Foundation - Shared Editor Fonts Style
 * (Font Awesome + Bebas)
 */
class CATALYSTFOUNDATIONEDITOR_API FCFEditorFontsStyle
{
public:
    // Lifecycle
    static void Initialize();
    static void Shutdown();
    static FName GetStyleSetName();
    static const ISlateStyle& Get();

    // Keys (Font Awesome + Bebas)
    static const FName IconSolid16;
    static const FName IconSolid24;
    static const FName IconSolid32;
    static const FName IconSolid48;
    static const FName IconRegular24;
    static const FName IconLight24;

    static const FName FontDisplay32;
    static const FName FontBody12;

    static const FName BebasBold20;
    static const FName BebasBook20;
    static const FName BebasLight20;
    static const FName BebasMiddle20;
    static const FName BebasRegular20;
    static const FName BebasThin20;

private:
    static TSharedRef<class FSlateStyleSet> Create();
private:
    static TSharedPtr<class FSlateStyleSet> StyleInstance;
};
