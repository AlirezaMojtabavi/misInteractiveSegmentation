#pragma once
#include"PlanData.h"

namespace parcast
{
	class PlanDataMatcher
	{
	public:
		explicit PlanDataMatcher(const PlanData& data) : m_Data(data)
		{}

		static bool IsEqual(const PlanData& a, const PlanData& b)
		{
			bool isEqual = true;
			isEqual = isEqual && (a.ImageUid == b.ImageUid);
			isEqual = isEqual && (a.PlanUid == b.PlanUid);
			isEqual = isEqual && (a.Brand == b.Brand);
			isEqual = isEqual && (a.Color.Red == b.Color.Red);
			isEqual = isEqual && (a.Color.Green == b.Color.Green);
			isEqual = isEqual && (a.Color.Blue == b.Color.Blue);
			isEqual = isEqual && (a.Color.Alpha == b.Color.Alpha);
			isEqual = isEqual && (a.Name == b.Name);
			isEqual = isEqual && (a.Location == b.Location);
			isEqual = isEqual && (a.Position == b.Position);
			isEqual = isEqual && (a.Length == b.Length);
			isEqual = isEqual && (a.Width == b.Width);
			isEqual = isEqual && (a.ObjectType == b.ObjectType);
			isEqual = isEqual && (a.Type == b.Type);
			isEqual = isEqual && (a.PlanLength == b.PlanLength);
			isEqual = isEqual && (a.PlanCentricAngle == b.PlanCentricAngle);
			return isEqual;
		}

		bool operator()(const PlanData& other) const
		{
			return IsEqual(m_Data, other);
		}

		PlanData m_Data;
	};

}
