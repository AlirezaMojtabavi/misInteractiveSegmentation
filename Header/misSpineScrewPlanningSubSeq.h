#pragma once

#include "IDatasetManager.h"
#include "INavigationViewersNView.h"
#include "IPackageDataVisualizer.h"
#include "IPlanningHelper.h"
#include "ISimpleDataPackage.h"
#include "misPackageDataVisualizer.h"
#include "VolumeMaker.h"
#include "IPlanningHelperUIUpdater.h"
#include "ISpinousToPlanAngleMeasurment.h"
#include "IPlanninghCutDirection.h"
#include "misPlanSTRCT.h"

namespace parcast
{
	class VisibilityManagement;
}
using namespace parcast;
//The class manage adding and updating screw plan to  viewer and data packages
class misSpineScrewPlanningSubSeq : public misMultiViewSubSequence
{
public:
	igstkStandardClassBasicTraitsMacro(misSpineScrewPlanningSubSeq, misMultiViewSubSequence);

	misSpineScrewPlanningSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<parcast::VolumeMaker> volumeMaker, std::shared_ptr<misSoftwareInformation> softwareInformation);
	misSpineScrewPlanningSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		IDatasetManager* datasetManager,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer, std::shared_ptr<IPlanningHelper> planningHelper,
		const std::string& sequenceName, const std::string& subsequenceName, std::shared_ptr<misSoftwareInformation> softwareInformation);

	void OnSelected();
	void TaskOnLeave();
	void Render();
	void RealseAllResources();
	bool ProcessRequest(misGUIEvent* pEvent );
	
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::shared_ptr<INavigationViewersNView> GetPlaningViewer();
	void AddPlanPoint( const misLandmarkInfoStruct& lndStr );
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;

private:

	void AcceptPlan(ScrewPlanInformation eventData);
	void InitializeObject();
	void CompleteProcess( itk::Object *caller,const itk::EventObject& pEvent);
	misEventListTypedef GetEventToGui();
	void UpdateVolume();
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<IPlanningHelper> m_PlanningHelper;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IPlanningHelperUIUpdater> m_PlanningHelperUIUpdater;
	std::unique_ptr<ISpinousToPlanAngleMeasurment> m_PlanToSpinousMeasuremnt;
	bool m_StartStopAngleMeasurement = false;
	std::unique_ptr<IPlanninghCutDirection> m_PlannngCutDirection;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
};