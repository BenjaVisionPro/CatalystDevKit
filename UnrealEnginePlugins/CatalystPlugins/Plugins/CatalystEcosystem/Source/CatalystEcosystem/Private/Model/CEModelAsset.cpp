#include "Model/CEModelAsset.h"

FString UCEModelAsset::GetSummaryText() const
{
	const int32 Ecosystems = Model.Ecosystems.Num();
	const int32 Biomes     = Model.Biomes.Num();
	const int32 Species    = Model.Animals.Num();
	const int32 Resources  = Model.Resources.Num();

	return FString::Printf(TEXT("Ecosystems: %d  |  Biomes: %d  |  Species: %d  |  Resources: %d"),
		Ecosystems, Biomes, Species, Resources);
}