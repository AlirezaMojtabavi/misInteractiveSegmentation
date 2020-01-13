#pragma once

namespace parcast
{

	// Called before saving legacy plan data from a dataset manager to database when there's a need for converting the plan data
	// to their spatial transforms relative to their parent image and setting the transform to correlation manager so the 
	// package-image is automatically saved to the correlation manager without needing extra information in the plan itself.
	class IPlanCoordSysConverter
	{
	public:
		virtual void Convert() = 0;

		virtual ~IPlanCoordSysConverter() = default;
	};

}