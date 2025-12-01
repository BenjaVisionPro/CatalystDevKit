// Copyright © Catalyst

#include "Runtime/CLCoordinateSpace.h"

// We avoid including a private header: expose a factory function from the
// geodesic .cpp and link against it instead.
extern const ICLCoordinateSpace& CL_GetGeodesicCoordSpace();

const ICLCoordinateSpace& FCLCoordSpaceRegistry::Resolve(ECLCoordSpace Space)
{
	switch (Space)
	{
	case ECLCoordSpace::Geodesic:
	default:
		return CL_GetGeodesicCoordSpace();
	}
}