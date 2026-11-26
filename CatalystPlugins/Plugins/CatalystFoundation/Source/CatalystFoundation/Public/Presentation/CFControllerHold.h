#pragma once

#include "CoreMinimal.h"

struct FCFControllerHoldIndicator
{
    static constexpr int32 Segments = 5;

    int32 Completed = 0;
    bool bFlashOn = false;
    bool bAnimating = false;
};

/** A hold is tied to the action target that was focused when the button went down. */
class FCFControllerHold
{
public:
    explicit FCFControllerHold(int32 InHoldTimeMs, int32 InFlashIntervalMs = 30)
        : HoldSeconds(FMath::Max(1, InHoldTimeMs) / 1000.0),
          FlashSeconds(FMath::Max(1, InFlashIntervalMs) / 1000.0)
    {
    }

    bool Update(bool bDown, const FGuid& Focus, double Now)
    {
        const bool bPressed = bDown && !bWasDown;
        bWasDown = bDown;
        if (Now - Confirmed < ConfirmationSeconds)
        {
            return false;
        }
        if (bPressed && Focus.IsValid())
        {
            Target = Focus;
            Started = Now;
            UnwindSegments = 0;
        }
        if (!Target.IsValid())
        {
            return false;
        }
        if (!bDown || Focus != Target)
        {
            UnwindSegments = FMath::Min(FCFControllerHoldIndicator::Segments, SegmentAt(Now) + 1);
            UnwindStarted = Now;
            Target.Invalidate();
            return false;
        }
        if (Now - Started < HoldSeconds)
        {
            return false;
        }
        Target.Invalidate();
        Confirmed = Now;
        return true;
    }

    FCFControllerHoldIndicator GetIndicator(double Now) const
    {
        const double SinceConfirmation = Now - Confirmed;
        if (SinceConfirmation < ConfirmationSeconds)
        {
            const bool bOn = (SinceConfirmation >= ConfirmationOffSeconds && SinceConfirmation < ConfirmationCycleSeconds)
                || SinceConfirmation >= ConfirmationCycleSeconds + ConfirmationOffSeconds;
            return {bOn ? FCFControllerHoldIndicator::Segments : 0, false, true};
        }
        if (Target.IsValid())
        {
            const int32 Current = SegmentAt(Now);
            const double SegmentElapsed = FMath::Max(0.0, Now - Started - Current * SegmentSeconds());
            return {Current, FMath::FloorToInt(SegmentElapsed / FlashSeconds) % 2 == 0, true};
        }

        const double UnwindElapsed = Now - UnwindStarted;
        if (UnwindElapsed < UnwindSegments * UnwindStepSeconds)
        {
            return {UnwindSegments - FMath::FloorToInt(UnwindElapsed / UnwindStepSeconds), false, true};
        }
        return {};
    }

private:
    static constexpr double ConfirmationOffSeconds = .05;
    static constexpr double ConfirmationOnSeconds = .10;
    static constexpr double ConfirmationCycleSeconds = ConfirmationOffSeconds + ConfirmationOnSeconds;
    static constexpr double ConfirmationSeconds = 2.0 * ConfirmationCycleSeconds;
    static constexpr double UnwindStepSeconds = .05;

    double SegmentSeconds() const { return HoldSeconds / FCFControllerHoldIndicator::Segments; }

    int32 SegmentAt(double Now) const
    {
        return FMath::Clamp(FMath::FloorToInt((Now - Started) / SegmentSeconds()), 0, FCFControllerHoldIndicator::Segments - 1);
    }

    double HoldSeconds;
    double FlashSeconds;
    double Started = 0.0;
    double Confirmed = -1.0;
    double UnwindStarted = 0.0;
    int32 UnwindSegments = 0;
    FGuid Target;
    bool bWasDown = false;
};
