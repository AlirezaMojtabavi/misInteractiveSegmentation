#pragma once

#include "BusinessEntities\Point.h"

namespace parcast
{

	typedef std::vector<unsigned char> ByteArray;

	class IPointListCodec
	{
	public:
		virtual std::shared_ptr<ByteArray> ToByteArray(const std::vector<Point<double, 3>> arr) const = 0;
		virtual std::vector<Point<double, 3>> FromByteArray(const ByteArray& byteArray, int numberOfPoints) const = 0;

		virtual ~IPointListCodec() = default;
	};

}