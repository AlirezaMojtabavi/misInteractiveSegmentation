#pragma once

#include "ITrackingTool.h"
#include "mis3DViewer.h"
#include "misEventFromGui.h"
#include "misSubSequence.h"
#include "ITrackingSubsequenceViews.h"
#include "misTrackingSequenceHelper.h"

class  misMicronTrackingSubsequence : public misSubSequence, public ITrackingSubsequenceViews
{
public:

	misMicronTrackingSubsequence(std::shared_ptr<ISubsequenceLayout> model,
	 std::shared_ptr<ITrackerConfigure> trackingConfig,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager , std::shared_ptr<misSoftwareInformation> softwareInformation);

	virtual void InitialeGuiProcessing();
	void MakeCameraFrustumPlaneForMicronTracker();
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
	misEventListTypedef	GetEventToGui() override;
	std::vector<std::shared_ptr<I3DViewer>>	GetAllViewers();
	bool ConnectToTracker() override;
	std::shared_ptr<misTrackingSequenceHelper> GetTrackerHelper() const override;

private:

	tgt::dvec3 GetUpView();
	std::shared_ptr<misSurfaceRepresentation> CameraObject(std::string fileName) override;
	void UpdateViewOnCalibration() override;
	void SetCSCorrelationManager(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> val);
	void InitializeRenderingView() const;
	void SetStateToUnderGoing();
	std::shared_ptr<ITrackerConfigure>	m_TrackingInitializer;
	std::shared_ptr<misTrackingSequenceHelper> m_TrackingViewHelper;
	misApplicationSetting*  m_AppSetting;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;

};