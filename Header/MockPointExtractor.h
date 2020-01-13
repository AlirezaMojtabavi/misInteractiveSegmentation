#pragma once

#include "IPointExtractor.h"

#include <turtle/mock.hpp>
#include <itkPoint.h>


MOCK_BASE_CLASS(MockPointExtractor, IPointExtractor)
{
	typedef itk::Point<double, 3> PointType;
	MOCK_CONST_METHOD(GetPoints,0 , std::vector<PointType> ());
};
