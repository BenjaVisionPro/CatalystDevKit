// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"

/**
 * FBVCBoundedMpscQueue<T>
 *
 * - Multi-producer, single-consumer wrapper around TQueue<T, Mpsc>
 * - Enforce a hard capacity in producer path (TryEnqueue fails when full)
 * - Track depth, peak depth, and drop count
 *
 * Notes:
 * - Uses UE 5.6-compatible TAtomic API: Load/Store/CompareExchange/Inc/Dec only.
 * - Moveable, not copyable (so we can reconfigure capacities by swapping instances).
 */
template <typename T>
class FBVCBoundedMpscQueue
{
public:
    explicit FBVCBoundedMpscQueue(int32 InCapacity = 1024)
        : Capacity(FMath::Max(1, InCapacity))
    {}

    // Non-copyable
    FBVCBoundedMpscQueue(const FBVCBoundedMpscQueue&)            = delete;
    FBVCBoundedMpscQueue& operator=(const FBVCBoundedMpscQueue&) = delete;

    // Moveable (allows replacing queues in Configure())
    FBVCBoundedMpscQueue(FBVCBoundedMpscQueue&& Other) noexcept
        : Q(MoveTemp(Other.Q))
        , Capacity(Other.Capacity)
    {
        Depth.Store(Other.Depth.Load());
        MaxDepth.Store(Other.MaxDepth.Load());
        Drops.Store(Other.Drops.Load());
        Other.Depth.Store(0);
        Other.MaxDepth.Store(0);
        Other.Drops.Store(0);
    }

    FBVCBoundedMpscQueue& operator=(FBVCBoundedMpscQueue&& Other) noexcept
    {
        if (this != &Other)
        {
            Q        = MoveTemp(Other.Q);
            Capacity = Other.Capacity;

            Depth.Store(Other.Depth.Load());
            MaxDepth.Store(Other.MaxDepth.Load());
            Drops.Store(Other.Drops.Load());

            Other.Depth.Store(0);
            Other.MaxDepth.Store(0);
            Other.Drops.Store(0);
        }
        return *this;
    }

public:
    // Try to enqueue by value
    bool TryEnqueue(const T& Item)
    {
        if (!ReserveOneSlot())
        {
            Drops.IncrementExchange();
            return false;
        }

        Q.Enqueue(Item);
        UpdateMaxDepthAfterPush();
        return true;
    }

    // Try to enqueue by move
    bool TryEnqueue(T&& Item)
    {
        if (!ReserveOneSlot())
        {
            Drops.IncrementExchange();
            return false;
        }

        Q.Enqueue(MoveTemp(Item));
        UpdateMaxDepthAfterPush();
        return true;
    }

    // Single-consumer dequeue
    bool Dequeue(T& Out)
    {
        if (!Q.Dequeue(Out))
        {
            return false;
        }
        Depth.DecrementExchange();
        return true;
    }

    // Non-destructive peek (single-consumer)
    bool Peek(T& Out) const
    {
        return Q.Peek(Out);
    }

    // Metrics
    int32 GetCapacity()  const { return Capacity; }
    int32 GetDepth()     const { return Depth.Load(); }
    int32 GetPeak()      const { return MaxDepth.Load(); }
    int32 GetDrops()     const { return Drops.Load(); }
    void  ResetDrops()         { Drops.Store(0); }

    // Clear queue and reset counters (single-consumer context)
    void Reset()
    {
        T tmp;
        while (Q.Dequeue(tmp)) { /* drain */ }
        Depth.Store(0);
        MaxDepth.Store(0);
        Drops.Store(0);
    }

private:
    // Reserve one slot by atomically incrementing Depth if < Capacity
    bool ReserveOneSlot()
    {
        for (;;)
        {
            const int32 Cur = Depth.Load();
            if (Cur >= Capacity)
            {
                return false; // full
            }

            int32 Expected = Cur;                  // must be non-const lvalue
            const int32 Desired = Cur + 1;

            if (Depth.CompareExchange(Expected, Desired))
            {
                return true; // incremented
            }
            // else: Expected now holds the current depth; retry
        }
    }

    // Track high-water mark
    void UpdateMaxDepthAfterPush()
    {
        const int32 Cur = Depth.Load();
        int32 Prev = MaxDepth.Load();

        // Raise MaxDepth to Cur if Cur is larger
        while (Cur > Prev)
        {
            int32 Expected = Prev; // non-const lvalue
            if (MaxDepth.CompareExchange(Expected, Cur))
            {
                break; // updated
            }
            // CAS failed; Expected holds latest MaxDepth
            Prev = Expected;
        }
    }

private:
    TQueue<T, EQueueMode::Mpsc> Q;
    int32                       Capacity = 1024;

    // Updated by producers/consumer as documented above
    mutable TAtomic<int32> Depth   {0};
    mutable TAtomic<int32> MaxDepth{0};
    mutable TAtomic<int32> Drops   {0};
};
