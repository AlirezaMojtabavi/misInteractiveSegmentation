#pragma once
#include "misPlanFlowInformation.h"
#include "misPlanData.h"
#include "IPlanFlowUIAdapter.h"
#include "INavigationViewersNView.h"
#include "misVolumeCropping.h"
#include "misCroppingDirectionInVR.h"
#include "IBiopsyPlanningFlow.h"

class BiopsyPlanningFlow  :public IBiopsyPlanningFlow
{
public:
	BiopsyPlanningFlow(std::shared_ptr<misPlanFlowInformation> planeFlowInformation,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IVolumeCropping> volumeCropping,
		std::shared_ptr<IPlanFlowUIAdapter>,
		const PlanFlowParameter planningFlowParam);


	void StartPlanFlow(std::shared_ptr<IPlan> planReadytoFlow, misCineDirection planFlowDirection,
		misCroppingDirectionInVR croppingDir = NoCut) override;
	void SetPlanFlowSlider(const double& value, std::weak_ptr<IPlan> plnData,
		misCineDirection planFlowDirection) override;
	void StopPlanFlow() override;
private:
	std::shared_ptr<misPlanFlowInformation> m_PlaneFlowInformation;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IVolumeCropping> m_VolumeCropping;
	std::shared_ptr<IPlanFlowUIAdapter> m_PlanFlowUiAdapter;
	bool m_IsPreviewStart = false;
	int m_PlanFlowStepSize = 50;
	void UpdateCroppingDirection(misCroppingDirectionInVR croppingDir);
	void Render();
};





