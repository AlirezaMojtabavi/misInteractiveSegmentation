#pragma once
struct ApproachAndModelVisibilityInformation;

namespace parcast
{
	class IVisibilityMangement
	{
	public:
		virtual void SetVisibility(const ApproachAndModelVisibilityInformation& pEvent) = 0;
		virtual void SetVisibility2D(const ApproachAndModelVisibilityInformation& pEvent) = 0;
		virtual void SetVisibility3D(const ApproachAndModelVisibilityInformation& pEvent) = 0;
	};
}
