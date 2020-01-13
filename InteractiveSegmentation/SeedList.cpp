
#include "pch.h"
#include "SeedList.h"
SeedList::SeedList(std::vector<coordinate3D> pointList, std::vector<double> Intensity)
	:m_PointList(pointList), m_Intensity(Intensity)
{
}  

std::vector<coordinate3D> SeedList::get_vector()
{
	return m_PointList;
}
 



double * SeedList::get_min_max()
{
	std::vector<double>min;
	std::vector<double>max;
	double threshold[2];

	if (!*threshold)
	{
		threshold[0] = m_Intensity[0];
		threshold[1] = m_Intensity[0];
	}

	int size = m_Intensity.size();


	for (int i = 0; i < size; i++)
	{
		if (m_Intensity[i] <= threshold[0] && m_Intensity[i] > 100)
		{
			threshold[0] = m_Intensity[i];
			min.push_back(threshold[0]);
		}

		if (m_Intensity[i] >= threshold[1])
		{
			threshold[1] = m_Intensity[i];
			max.push_back(threshold[1]);
		}
	}

	threshold[0] = min.back();
	threshold[1] = max.back();

	return threshold;
}
 
 