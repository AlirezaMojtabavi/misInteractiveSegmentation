#pragma once

//-----------------------------------------------------------------------------
// Sort regions from front to back.
//-----------------------------------------------------------------------------
class vtkRegionDistance2
{
public:
	size_t Id; // 0<=Id<27
	// square distance between camera center to region center: >=0
	double Distance2;
};
extern "C" int vtkRegionComparisonFunction(const void *x,
	const void *y);