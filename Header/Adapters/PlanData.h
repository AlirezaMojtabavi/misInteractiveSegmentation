#pragma once

namespace parcast
{

	struct PlanData
	{

		struct ColorType
		{
			long long int Red;
			long long int Green;
			long long int Blue;
			double Alpha;
		};

		std::string PlanUid;
		std::string ImageUid;
		std::string Name;
		long long int ObjectType;
		ColorType Color;
		double Length;
		double Width;
		long long int Position;
		long long int Location;
		long long int Type;
		long long int Brand;
		double PlanLength;
		double PlanCentricAngle;
	};

}
