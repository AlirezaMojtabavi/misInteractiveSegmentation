#pragma once

#include "misStringTools.h"
#include "SolutionData.h"

namespace parcast
{

	class ISolutionDataAccess
	{
	public:
		virtual std::vector<SolutionData> GetAll() = 0;
		virtual SolutionData GetById(const std::string& id) = 0;
		virtual void DeleteAll() = 0;
		virtual void DeleteById(const std::string& id) = 0;
		virtual void InsertOrUpdate(const SolutionData& inSolutionData) = 0;
		virtual bool PatientUidExists(const std::string& id) = 0;
		virtual ~ISolutionDataAccess() { }
	};

}
