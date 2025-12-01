#pragma once
#include "CoreMinimal.h"
#include "Async/Async.h"

namespace BVC
{
    inline void EnqueueOnGameThread(TFunction<void()>&& Fn)
    {
        // If we’re already on the game thread, run immediately.
        if (IsInGameThread())
        {
            Fn();
            return;
        }

        // Otherwise hop to the game thread.
        AsyncTask(ENamedThreads::GameThread, [Task = MoveTemp(Fn)]() mutable
        {
            Task();
        });
    }
}
