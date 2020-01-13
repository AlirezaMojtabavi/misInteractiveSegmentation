#pragma once

#include "DateTimeMatcher.h"
#include "SolutionData.h"


namespace parcast
{
	
	class SolutionDataMatcher
	{
	public:
		SolutionDataMatcher(const SolutionData& solutionData) : m_SolutionData(solutionData) { }

		bool operator()(const SolutionData& other) const 
		{
			return IsEqual(m_SolutionData, other);
		}

		static bool IsEqual(const SolutionData& a, const SolutionData& b)
		{
			return a.SolutionUid == b.SolutionUid &&
				a.PatientUid == b.PatientUid &&
				DateTimeMatcher::IsEqual(a.DateTimeOfCreation, b.DateTimeOfCreation) &&
				DateTimeMatcher::IsEqual(a.DateTimeOfModification, b.DateTimeOfModification) &&
				a.IsViewable == b.IsViewable &&
				a.LastSelectedSubTabName == b.LastSelectedSubTabName &&
				a.LastSelectedTabName == b.LastSelectedTabName &&
				a.SolutionFolderName == b.SolutionFolderName &&
				a.UserId == b.UserId &&
				a.RegisteredImageUid == b.RegisteredImageUid &&
				a.RegisteredReferenceUid == b.RegisteredReferenceUid;
		}

	private:
		const SolutionData& m_SolutionData;
	};

}
