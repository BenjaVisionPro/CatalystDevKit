#include "Schema/UBVCSchemaRegistry.h"

// Per-registry, per-catalog index (lives only in this TU)
namespace
{
    struct FIndex
    {
        FGuid CatalogId;
        FString Hash;
        TMap<FString, int32> NameToIndex;
    };

    static TMap<const UBVCSchemaRegistry*, FIndex> GRegistryIndex;

    static void EnsureIndexUpToDate(const UBVCSchemaRegistry* Reg, const FBVCMADescriptionContainer& Catalog)
    {
        FIndex& Ix = GRegistryIndex.FindOrAdd(Reg);
        if (Ix.CatalogId == Catalog.CatalogId && Ix.Hash == Catalog.Hash && Ix.NameToIndex.Num() == Catalog.Descriptions.Num())
        {
            return; // looks current
        }

        Ix.CatalogId = Catalog.CatalogId;
        Ix.Hash = Catalog.Hash;
        Ix.NameToIndex.Reset();

        for (int32 i = 0; i < Catalog.Descriptions.Num(); ++i)
        {
            // Note: Magritte names are case sensitive on the server; mirror here.
            Ix.NameToIndex.Add(Catalog.Descriptions[i].Name, i);
        }
    }
}

bool UBVCSchemaRegistry::FindByName(FName ClassName, FBVCMADescription& OutDescription) const
{
    EnsureIndexUpToDate(this, Catalog);

    const FString Wanted = ClassName.ToString();

    if (const FIndex* Ix = GRegistryIndex.Find(this))
    {
        if (const int32* FoundIdx = Ix->NameToIndex.Find(Wanted))
        {
            OutDescription = Catalog.Descriptions[*FoundIdx];
            return true;
        }
    }

    // Fallback (should rarely happen unless index not built yet)
    for (const FBVCMADescription& D : Catalog.Descriptions)
    {
        if (D.Name == Wanted)
        {
            OutDescription = D;
            return true;
        }
    }
    return false;
}
