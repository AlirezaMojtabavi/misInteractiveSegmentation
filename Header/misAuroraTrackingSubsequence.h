#pragma once

#include "ITrackingTool.h"
#include "mis3DViewer.h"
#include "misEventFromGui.h"
#include "misSubSequence.h"
#include "ITrackingSubsequenceViews.h"
#include "misTrackingSequenceHelper.h"
#include "ITrackerConfigure.h"

class igstkTracker;
class misTrackingToolQuery;
class misToolRepresentation;
class ITrackingTool;

class  misAuroraTrackingSubsequence :public misSubSequence, public ITrackingSubsequenceViews
{
public:
	misAuroraTrackingSubsequence(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		std::shared_ptr<ISubsequenceLayout> model,
		 std::shared_ptr<ITrackerConfigure> trackingConfig, std::shared_ptr<misSoftwareInformation> softwareInformation);

	virtual void InitialeGuiProcessing();
	void UpdateXYZView() override;
	void UpdateTopView(double * bound) override;
	void UpdateSideView(double * bound) override;
	void UpdateFrontView(double * bound) override;
	void UpdateStatus(long long int puls) override;
	bool ProcessRequest(misGUIEvent* pEvebt) override;
	void OnSelected() override;
	void TaskOnLeave() override;
	void ResetSetting() override;
	void Render() override;
	void AddTrackerTool(std::shared_ptr<ITrackingTool>  pTracker);
	void RealseAllResources() override;
	misEventListTypedef GetEventToGui();
	virtual std::vector<std::shared_ptr<I3DViewer>>	GetAllViewers();
	void misAuroraTrackingSubsequence::AddObserversAddToolsMakeFrustum(misToolPropertiesListTypdef ListOfTools);
	// Connect to tracker
	bool ConnectToTracker();
	std::shared_ptr<misTrackingSequenceHelper> GetTrackerHelper() const override;

private:
	void UpdateViewOnCalibration();
	void InitializeRenderingView() const;
	std::shared_ptr<misSurfaceRepresentation> CameraObject(std::string fileName) override;
	void MakeCameraAndFrustum();
	void SetStateToUnderGoing();

	bool m_TrackerDisconnectMsgAlreadyShown;
	std::vector<misToolRepresentation*> m_ToolList1;
	std::vector<misToolRepresentation*> m_ToolList2;
	std::vector<misToolRepresentation*> m_ToolList3;
	std::vector<misToolRepresentation*> m_ToolList4;
	std::shared_ptr<ITrackerConfigure> m_TrackingInitializer;
	misApplicationSetting* m_AppSetting;
	std::shared_ptr<misTrackingSequenceHelper> m_TrackingViewHelper;
	misTrackingStateReport m_LastRequiredToolInfo;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
};