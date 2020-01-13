#pragma once
#include "ILandmarkVisibilty.h"
#include "ICornerProperties.h"

class LandmarkVisibilty :
	public ILandmarkVisibilty
{
public:
	LandmarkVisibilty(std::shared_ptr<ICornerProperties>, double differenceForViewingSeed);
	~LandmarkVisibilty() = default;
	virtual void CheckVisibility(const LandmarkListType& landMarkList) const override;

 private:
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	double m_DifferenceForViewingSeed;
};

