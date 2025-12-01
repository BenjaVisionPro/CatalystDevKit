// ============================================================================
// CLStrata.cpp
// ============================================================================
#include "Model/CLStrata.h"

void FCLStrata::Sample(double AltitudeN, const bool bNormalize, TArray<FCLStratumSample>& OutSamples) const
{
	OutSamples.Reset();

	double Sum = 0.0;
	for (const FCLStratum& Stratum : Strata)
	{
		const double W = Stratum.ComputeWeight(AltitudeN);
		if (W > 0.0)
		{
			FCLStratumSample S;
			S.StratumId = Stratum.Id;   // from FCFAbstractObject base
			S.WeightN   = W;
			OutSamples.Add(S);
			Sum += W;
		}
	}

	if (bNormalize && Sum > 0.0)
	{
		const double Inv = 1.0 / Sum;
		for (FCLStratumSample& S : OutSamples)
		{
			S.WeightN *= Inv;
		}
	}
}