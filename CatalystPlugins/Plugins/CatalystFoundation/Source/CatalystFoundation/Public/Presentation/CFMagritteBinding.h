#pragma once

#include "CoreMinimal.h"

#pragma push_macro("check")
#undef check
THIRD_PARTY_INCLUDES_START
#include <magritte/magritte.hpp>
THIRD_PARTY_INCLUDES_END
#pragma pop_macro("check")

class ULocalPlayer;

/** A view of one object in an authorized, retained Magritte graph. */
class FCFMagritteBinding
{
public:
    static TOptional<FCFMagritteBinding> Find(
        std::shared_ptr<const magritte::Graph> Graph, const std::string& ObjectId)
    {
        if (!Graph)
        {
            return {};
        }
        const auto It = Graph->objects.find(ObjectId);
        if (It == Graph->objects.end() || !It->second.description)
        {
            return {};
        }
        return FCFMagritteBinding(std::move(Graph), It->second);
    }

    const magritte::Description& Describe() const { return *Model->description; }

    magritte::Value Read(const magritte::Description& Field) const
    {
        return Model->readUsing(Field);
    }

    const std::string& ObjectId() const { return Model->id; }

    TOptional<FCFMagritteBinding> Follow(const magritte::Description& Field) const
    {
        if (Field.isRelation() && !Field.isMultiple())
        {
            const auto Value = Read(Field);
            if (const auto* Reference = std::get_if<magritte::Value::Reference>(&Value.data))
            {
                return Find(Graph, Reference->id);
            }
        }
        return {};
    }

    TOptional<FCFMagritteBinding> Follow(const std::string& FieldId) const
    {
        for (const auto& Field : Describe().orderedChildren())
        {
            if (Field->id == FieldId)
            {
                return Follow(*Field);
            }
        }
        return {};
    }

    TOptional<FCFMagritteBinding> FirstRelated(const std::string& FieldId) const
    {
        for (const auto& Field : Describe().orderedChildren())
        {
            if (Field->id == FieldId && Field->isRelation() && Field->isMultiple())
            {
                const auto Value = Read(*Field);
                if (!Value.isCollection())
                {
                    break;
                }
                const auto Values = Value.elements();
                if (!Values.empty())
                {
                    if (const auto* Ref = std::get_if<magritte::Value::Reference>(&Values.front().data))
                    {
                        return Find(Graph, Ref->id);
                    }
                }
                break;
            }
        }
        return {};
    }

    TArray<FCFMagritteBinding> Related(const std::string& FieldId, int32 Limit) const
    {
        TArray<FCFMagritteBinding> Result;
        for (const auto& Field : Describe().orderedChildren())
        {
            if (Field->id == FieldId && Field->isRelation() && Field->isMultiple())
            {
                const auto Value = Read(*Field);
                if (Value.isCollection())
                {
                    for (const auto& Element : Value.elements())
                    {
                        if (Result.Num() >= Limit)
                        {
                            break;
                        }
                        if (const auto* Ref = std::get_if<magritte::Value::Reference>(&Element.data))
                        {
                            if (auto Object = Find(Graph, Ref->id))
                            {
                                Result.Add(MoveTemp(*Object));
                            }
                        }
                    }
                }
                break;
            }
        }
        return Result;
    }

private:
    FCFMagritteBinding(std::shared_ptr<const magritte::Graph> InGraph,
        const magritte::AdaptiveModel& InModel)
        : Graph(std::move(InGraph)), Model(&InModel)
    {
    }

    std::shared_ptr<const magritte::Graph> Graph;
    const magritte::AdaptiveModel* Model;
};

/** Implemented by the game session adapter. All calls and updates run on the game thread. */
class ICFPlayerMagritteSource
{
public:
    virtual ~ICFPlayerMagritteSource() = default;

    /** Read the authenticated user's current graph for this player, or empty while unavailable. */
    virtual TOptional<FCFMagritteBinding> SignedInUser(const ULocalPlayer& Player) const = 0;

    /** Broadcast on replacement, profile change or sign-out. */
    virtual FSimpleMulticastDelegate& OnChanged() = 0;
};
