#pragma once

namespace parcast
{

	typedef std::shared_ptr<std::vector<std::uint8_t>> ByteArrayPtr;

	struct PanoramicData
	{
		std::string ImageUid;
		long long int NumberOfPoints;
		ByteArrayPtr Points;
	};

}
