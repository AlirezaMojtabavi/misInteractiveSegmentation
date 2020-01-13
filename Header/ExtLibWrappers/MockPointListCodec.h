#pragma once

#include "IPointListCodec.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPointListCodec, IPointListCodec)
	{
		typedef std::vector< Point<double, 3> > PointListType;
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const std::vector<Point<double, 3>> arr));
		MOCK_CONST_METHOD(FromByteArray, 2, PointListType (const ByteArray& byteArray, int numberOfPoints));
	};

}

