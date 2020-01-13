#ifndef _misStrctSolution_H
#define _misStrctSolution_H

#include "misPrimaeryNeededHeader.h"

struct misPackageStatus
{
	vector<int>  imagesDependencyStatus;
	vector<int>  polydataDependencyStatus;
	vector<int>  volumedataDependencyStatus;
	vector<int>  planDependencyStatus;
};

struct misSolutionAbstractStatus
{
	vector<int>                imagesStatus;
	vector<int>                polydataStatus;
	vector<int>                imageCorrelationStatus;
	vector<misPackageStatus>   packageStatus;

};

namespace misSoloution    
{
	//typedef misImage<float,3>  ImageType;
	//	typedef itk::ImageSeriesReader< misSoloution::ImageType >    ReaderType;
};


#endif