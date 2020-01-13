#pragma once

#include "DentalPlanningUiUserSide.h"
#include "ISplineVisualizer.h"
#include "misMultiViewSubSequence.h"

//The class manage adding and updating screw plan to  viewer and data packages
class misDentalPlanningSubsequence : public misMultiViewSubSequence
{
public:

	misDentalPlanningSubsequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		misApplicationType applicationType);

	void InitialeGuiProcessing();
	void RequestInitializeGUI(std::shared_ptr<ISubsequenceLayout> dataTab );
	void OnSelected();
	void TaskOnLeave();
	bool ProcessRequest(misGUIEvent* pEvent);

	virtual std::shared_ptr<INavigationViewersNView> GetGroupViewer() const ;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:

	void CreateObjects();
	void InitializeObject();

	misEventListTypedef GetEventToGui();

	void ResetSetting();
	virtual void Render();
	virtual void RealseAllResources();
	virtual std::vector<std::shared_ptr<I3DViewer>> GetAllViewers();

	std::shared_ptr<parcast::DentalPlanningUiUserSide> m_UiUserSide;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
};