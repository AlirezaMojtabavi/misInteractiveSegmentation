#pragma once

#include "misEnums.h"
#include "misStringTools.h"
#include "misSolutionProperty.h"

namespace parcast
{
	class ISolutionPatientDataAdapter
	{
	public:
		virtual std::vector<misSolutionProperty> GetAllSolutions() = 0;
		virtual void ReadSolutionInformation(const misUID& solutionUid) = 0;
		virtual void DeleteSolution(const misUID& solutionUid) = 0;
		virtual void SaveSolutionInformation() = 0;
		virtual void SaveSolutionInformationWithoutRegistration() = 0;
		virtual void DeleteAllSolutions() = 0;
		virtual ~ISolutionPatientDataAdapter() { }
	};

}