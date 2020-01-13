#pragma once
#include "IPlanninghCutDirection.h"
#include "INavigationViewersNView.h"


class misPlanninghCutDirection :	public IPlanninghCutDirection
{
public:
	misPlanninghCutDirection(std::shared_ptr<INavigationViewersNView> planningViewers);
	~misPlanninghCutDirection() = default;
	void SetCroppingDirection(misCroppingDirectionInVR croppingDirection) override;
	void UpdateCutPlanes() override;

private:
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	misCroppingDirectionInVR m_CroppingDirection{ NoCut };
};

