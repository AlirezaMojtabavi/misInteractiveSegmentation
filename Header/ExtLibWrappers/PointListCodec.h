#pragma once

#include "IPointListCodec.h"

namespace parcast 
{

	class PointListCodec :public IPointListCodec
	{

		typedef std::vector<unsigned char> ByteArray;
	public:

		PointListCodec()
		{
		};

		virtual std::shared_ptr<ByteArray> ToByteArray(const std::vector<Point<double, 3>> pointlist) const override
		{
			std::vector<double> vectorizedData;
			vectorizedData.reserve(pointlist.size() * 3);

			for (auto const& point : pointlist)
			{
				vectorizedData.push_back(point[0]);
				vectorizedData.push_back(point[1]);
				vectorizedData.push_back(point[2]);
			}
			auto data = reinterpret_cast<unsigned char*>(vectorizedData.data());
			return std::make_shared<ByteArray>(data, data + vectorizedData.size() * sizeof(double));
		};

		virtual std::vector<Point<double, 3>> FromByteArray(const ByteArray& byteArray, int numberOfPoints) const override
		{
			auto pointList = std::vector<parcast::Point<double, 3>>();
			if (numberOfPoints == 0)
				return pointList;

			auto vectorizedData = reinterpret_cast<const double*>(byteArray.data());
			pointList.reserve(numberOfPoints);
			for (int i = 0; i < numberOfPoints; ++i)
				pointList.push_back(
					parcast::Point<double, 3>(vectorizedData[i * 3], vectorizedData[i * 3 + 1], vectorizedData[i * 3 + 2]));

			return pointList;
		};
	};

}
