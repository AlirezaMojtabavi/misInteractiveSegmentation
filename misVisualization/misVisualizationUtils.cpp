#include "stdafx.h"
#include "misVisualizationUtils.h"

#define distanceToLndForView 50

// coronal & sagittal multiplied by -1 temporarily
misVisualizationUtils::misVisualizationUtils(void)
{
}

misVisualizationUtils::~misVisualizationUtils(void)
{
}

bool misVisualizationUtils::CheckInFrustum( double* bounds, double* planes )
{
	double      center[3],screen_bounds[4];
	double               radius = 0.0,d,coverage;

	center[0] = (bounds[0] + bounds[1]) / 2.0;
	center[1] = (bounds[2] + bounds[3]) / 2.0;
	center[2] = (bounds[4] + bounds[5]) / 2.0;

	radius = 0.5 * sqrt( ( bounds[1] - bounds[0] ) *
		( bounds[1] - bounds[0] ) +
		( bounds[3] - bounds[2] ) *
		( bounds[3] - bounds[2] ) +
		( bounds[5] - bounds[4] ) *
		( bounds[5] - bounds[4] ) );

	for ( int i = 0; i < 6; i++ )
	{
		// Compute how far the center of the sphere is from this plane
		d =
			planes[i*4 + 0] * center[0] +
			planes[i*4 + 1] * center[1] +
			planes[i*4 + 2] * center[2] +
			planes[i*4 + 3];
		// If d < -radius the prop is not within the view frustum
		if ( d < -radius )
		{
			coverage = 0.0;
			return  false;
		}
		// The first four planes are the ones bounding the edges of the
		// view plane (the last two are the near and far planes) The
		// distance from the edge of the sphere to these planes is stored
		// to compute coverage.
		if ( i < 4 )
		{
			screen_bounds[i] = d - radius;
		}
		// The fifth plane is the near plane - use the distance to
		// the center (d) as the value to sort by
		if ( i == 4 )
		{
			//	distanceList[propLoop] = d;
		}



	}
	return true;
}


