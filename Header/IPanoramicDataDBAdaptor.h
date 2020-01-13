#pragma once
#include "misTypes.h"
// The IPanoramicDataDBAdaptor  store  and retrieve panoramic curve information from DB or any external storage - panoramic data
// include spline points and spline length that defines curve points and lengths
// 
class IPanoramicDataDBAdaptor
{
public:
	struct misPackagePanormaicData
	{
		std::vector<itk::Point<double, 3>> points;
		double length;
		std::string solutionUID;
		std::string packageUID;
		std::string parentImageUID;
	};
	// Save panoramic curve data to db or any external storage
	virtual bool Save(const misPackagePanormaicData& data) = 0;
		
	// Load panoramic curve data to db or any external storage
	virtual bool Load(misPackagePanormaicData& data) = 0;
	
	// Delete  panoramic curve information from db or any external storage
	virtual bool Delete(const std::string& solutionUID) = 0;

	virtual ~IPanoramicDataDBAdaptor(void){}
};

