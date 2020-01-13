#pragma once
#include "DateTimeMatcher.h"
#include "PatientData.h"

namespace  parcast
{
	class PatientDataMatcher
	{
	public:
		PatientDataMatcher(PatientData data) : m_PatientData(data) {}
		
		bool operator()(const PatientData& other) const
		{
			return IsEqual(m_PatientData, other);

		}

		static  bool IsEqual(const PatientData& a, const PatientData& b)
		{
			bool isEqual = true;
			isEqual = isEqual && b.PatientUID == a.PatientUID;
			isEqual = isEqual && DateTimeMatcher::IsEqual(b.BirthDate, a.BirthDate);
			isEqual = isEqual && b.FamilyName == a.FamilyName;
			isEqual = isEqual && b.Gender == a.Gender;
			isEqual = isEqual && b.Name == a.Name;
			isEqual = isEqual && b.NationalCode == a.NationalCode;
			isEqual = isEqual && b.Position == a.Position;
			isEqual = isEqual && b.Weight == a.Weight;
			return isEqual;
		}

	private:
		PatientData m_PatientData;

	};
}
