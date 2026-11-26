#pragma once

#include "CoreMinimal.h"
#include <map>
#include <string>
#include "CFObject.generated.h"

class UWidget;

struct FCFViewState
{
    std::map<std::string, std::string> SelectionByObject;
};

struct FCFViewContext
{
    UObject& Owner;
    TSharedRef<FCFViewState> State;
};
struct FCFObject;
namespace magritte { struct Description; }

/** Local presentation extension for a Magritte description container. */
struct CATALYSTFOUNDATION_API FCFViewDescription
{
    using FBuilder = UWidget* (*)(const FCFObject&, const magritte::Description&, const FCFViewContext&);

    const magritte::Description* Container = nullptr;
    FBuilder Build = nullptr;
};

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFObject
{
    GENERATED_BODY()

    virtual ~FCFObject() = default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catalyst")
    FName Icon = TEXT("circleQuestion");

    virtual FCFViewDescription MagritteDescription() const;
    UWidget* AsView(const FCFViewContext& Context) const;
};

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFIdentifiableObject : public FCFObject
{
    GENERATED_BODY()

    FCFIdentifiableObject();
    explicit FCFIdentifiableObject(FString InIdentifier);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catalyst", meta = (IgnoreForMemberInitializationTest))
    FString Identifier;
};

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFLabelledObject : public FCFIdentifiableObject
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catalyst")
    FString Label;
};
