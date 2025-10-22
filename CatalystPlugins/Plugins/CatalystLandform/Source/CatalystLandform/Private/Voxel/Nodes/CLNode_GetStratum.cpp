#include "Voxel/Nodes/CLNode_GetStratum.h"
#include "Model/CLStrataAsset.h"

void FVoxelNode_GetStratum::Compute(FVoxelGraphQuery Query) const
{
	bool bFound = false;

	double AltMin   = 0.0;
	double AltMax   = 0.0;
	double Tin      = 0.0;
	double Tout     = 0.0;
	int32  TinType  = 0;
	int32  ToutType = 0;
	FName  NameOut  = NAME_None;
	FGuid  IdOut;

	if (StrataAsset)
	{
		const TArray<FCLStratum>& Arr = StrataAsset->Strata.Strata;

		auto SetFrom = [&](const FCLStratum& S)
		{
			bFound   = true;
			AltMin   = S.AltitudeMinN;
			AltMax   = S.AltitudeMaxN;
			Tin      = S.TransitionInN;
			Tout     = S.TransitionOutN;
			TinType  = static_cast<int32>(S.TransitionInType);
			ToutType = static_cast<int32>(S.TransitionOutType);
			NameOut  = FName(*S.Title);
			IdOut    = S.Id;
		};

		if (Mode == ECLStratumLookupMode::ByTitle)
		{
			if (!Title.IsNone())
			{
				for (const FCLStratum& S : Arr)
				{
					if (S.Title == Title)
					{
						SetFrom(S);
						break;
					}
				}
			}
		}
		else // ByIndex
		{
			if (Arr.IsValidIndex(Index))
			{
				SetFrom(Arr[Index]);
			}
		}
	}

	FoundPin.Set(Query, bFound);
	AltitudeMinNPin.Set(Query, AltMin);
	AltitudeMaxNPin.Set(Query, AltMax);
	TransitionInNPin.Set(Query, Tin);
	TransitionOutNPin.Set(Query, Tout);
	TransitionInTypePin.Set(Query, TinType);
	TransitionOutTypePin.Set(Query, ToutType);
	OutTitlePin.Set(Query, NameOut);
	OutIdPin.Set(Query, IdOut);
}