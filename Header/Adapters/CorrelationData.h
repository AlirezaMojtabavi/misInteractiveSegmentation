#pragma once

namespace parcast
{

	typedef std::shared_ptr<std::vector<uint8_t>> ByteArrayPtr;

	struct CorrelationData
	{
		std::string SourceUid;
		std::string DestinationUid;
		std::string SolutionUid;
		ByteArrayPtr Transform;
	};

}
