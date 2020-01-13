#include "stdafx.h"
#include "..\Header\misSeedBoundingCalculator.h"
#include "misSimplePointType.h"


misSeedBoundingCalculator::misSeedBoundingCalculator(misSimplePointListType tFGSeedList)
	:m_FGSeedList(tFGSeedList)
{
	
}


misROI misSeedBoundingCalculator::GetSeedBounding(int* dimenstion, double* spacing)
{
	if (m_FGSeedList.empty())
		return {};
	std::vector<double> xCoordinates, yCoordinates, zCoordinates;
	for (auto seed : m_FGSeedList)
	{
		xCoordinates.push_back(seed[0] * spacing[0]);
		yCoordinates.push_back(seed[1] * spacing[1]);
		zCoordinates.push_back(seed[2] * spacing[2]);
	}	
	misROI result;
	result[0] = *std::min_element(std::begin(xCoordinates), std::end(xCoordinates));
	result[1] = *std::max_element(std::begin(xCoordinates), std::end(xCoordinates));
	result[2] = *std::min_element(std::begin(yCoordinates), std::end(yCoordinates));
	result[3] = *std::max_element(std::begin(yCoordinates), std::end(yCoordinates));
	result[4] = *std::min_element(std::begin(zCoordinates), std::end(zCoordinates));
	result[5] = *std::max_element(std::begin(zCoordinates), std::end(zCoordinates));
	result[0] -= 20 ;
	result[1] += 20;
	result[2] -= 20;
	result[3] += 20;
	result[4] -= 20;
	result[5] += 20;

	result[0] = clip(result[0], 0, dimenstion[0] * spacing[0]);
	result[1] = clip(result[1], 0, dimenstion[0] * spacing[0]);
	result[2] = clip(result[2], 0, dimenstion[1] * spacing[1]);
	result[3] = clip(result[3], 0, dimenstion[1] * spacing[1]);
	result[4] = clip(result[4], 0, dimenstion[2] * spacing[2]);
	result[5] = clip(result[5], 0, dimenstion[2] * spacing[2]);


	return result;
}

double misSeedBoundingCalculator::clip(double number, double lower, double upper)
{
	return std::max(lower, std::min(number, upper));
}
