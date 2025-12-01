// ============================================================================
// CLStratum.cpp
// ============================================================================
#include "Model/CLStratum.h"

double FCLStratum::ComputeWeight(double AltitudeN) const
{
	const double Min = AltitudeMinN;
	const double Max = AltitudeMaxN;
	if (Max <= Min) return 0.0;

	AltitudeN = FMath::Clamp(AltitudeN, 0.0, 1.0);
	if (AltitudeN < Min || AltitudeN > Max)
	{
		return 0.0;
	}

	const double Span          = Max - Min;
	const double InWidthAbs    = FMath::Clamp(TransitionInN  * Span, 0.0, Span);
	const double OutWidthAbs   = FMath::Clamp(TransitionOutN * Span, 0.0, Span);
	const double InEnd         = Min + InWidthAbs;         // end of ramp-in
	const double OutStart      = Max - OutWidthAbs;        // start of ramp-out

	// Ramp-in region: [Min .. InEnd]
	if (InWidthAbs > 0.0 && AltitudeN < InEnd)
	{
		const double t = (AltitudeN - Min) / InWidthAbs;     // 0..1
		return CLTransition::Eval01(TransitionInType, t);
	}

	// Plateau region: [InEnd .. OutStart]
	if (AltitudeN <= OutStart)
	{
		return 1.0;
	}

	// Ramp-out region: (OutStart .. Max]
	if (OutWidthAbs > 0.0 && AltitudeN <= Max)
	{
		const double u = (AltitudeN - OutStart) / OutWidthAbs; // 0..1
		return 1.0 - CLTransition::Eval01(TransitionOutType, u);
	}

	return 0.0;
}