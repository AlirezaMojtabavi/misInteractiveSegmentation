#pragma once

#include "CorrelationData.h"

namespace parcast
{

	class ICorrelationDataAccess
	{
	public:
		virtual void Insert(const std::vector<CorrelationData>& list) = 0;
		virtual std::vector<CorrelationData> GetBySolutionUid(const std::string& uid) = 0;
		virtual void DeleteBySolutionUid(const std::string& uid) = 0;
		virtual void DeleteByCoordSysUid(const std::string& uid) = 0;
		virtual void DeleteAll() = 0;
		virtual ~ICorrelationDataAccess() = default;
	};

}