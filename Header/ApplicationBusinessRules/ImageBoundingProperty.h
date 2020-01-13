#pragma once
#include "Vector.h"

struct ImageBoundingProperty final
{
	ImageBoundingProperty()
	{
	}

	ImageBoundingProperty(const int* extent, const double* spacing)
	{
		for (int i = 0; i < 6; i++)
		{
			Extent[i] = extent[i];
		}
		for (int i = 0; i < 3; i++)
		{
			Spacing[i] = spacing[i];
		}
	}

	parcast::Vector<int, 6> Extent;
	parcast::Vector<double, 3> Spacing;
};
