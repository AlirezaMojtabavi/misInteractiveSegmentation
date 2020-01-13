#pragma once

#include "misMathUtils.h"

//remove data that places out of specified range and return Mean of remained data . the range is defined by multiplying 
// a coefficient in  standard deviation of data.the range is controlled by changing Coefficient .
template <class T>
class misDataNoiseReduction
{
public:
	misDataNoiseReduction(std::vector<T> toolPositions)
		: m_Coefficient(1.5)
	{
		m_Data = toolPositions;
		ReductNoise(m_Data);
	}
	~misDataNoiseReduction(void)
	{

	}
	std::vector<T> GetFilteredDataBuffer()const
	{
		return m_Data;
	}
	void SetCoefficient(const double& coef)
	{
		m_Coefficient = coef;
	}
private:



	void ReductNoise( std::vector<T> &dataBuffer )
	{
		//				 1
		//StdDev = sqrt(---Sigma{(xi - mio)^2})
		//				 N
		//A coefficient to intensify the impact of StdDev(s)./this value is used to determine a margin to be used as a threshold to 
		// decide which data instances are outliers /and can be eliminated A vector of points which stores the results of calculated
		//tip offsets on gathered data
		double zeroElemnent[] = {0.0, 0.0, 0.0};
		T sum(zeroElemnent), mean(zeroElemnent);
		sum = std::accumulate(dataBuffer.begin(), dataBuffer.end(), sum);

		mean = sum / dataBuffer.size();

		//calculate standard deviation of data
		std::vector<double>  xPositions, yPositions, zPositions;
		std::for_each(dataBuffer.begin(), dataBuffer.end(), [&](T  pt)
		{
			xPositions.push_back(pt[0]);
			yPositions.push_back(pt[1]);
			zPositions.push_back(pt[2]);
		});
		double StdDev_x = misMathUtils::StdDeviation(xPositions, mean[0]);
		double StdDev_y = misMathUtils::StdDeviation(yPositions, mean[1]);
		double StdDev_z = misMathUtils::StdDeviation(zPositions, mean[2]);
		auto it = std::remove_if(dataBuffer.begin(), dataBuffer.end(),
			[&](T  Vec)->bool
		{
			if ((abs(Vec[0] - mean[0]) > (StdDev_x * m_Coefficient)) ||
				(abs(Vec[1] - mean[1]) > (StdDev_y * m_Coefficient)) ||
				(abs(Vec[2] - mean[2]) > (StdDev_z * m_Coefficient)))
			{
				return true;
			}
			return false;
		});
		dataBuffer.erase(it, dataBuffer.end());
	}

	std::vector<T>  m_Data;
	double m_Coefficient;
};

