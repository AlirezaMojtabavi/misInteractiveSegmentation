#include "ITrackingTool.h"
#include "mis3DViewer.h"
#include "misEventFromGui.h"
#include "misSubSequence.h"
#include "misToolConfiguration.h"
#include "misTrackerConfigure.h"
#include "ITrackingSubsequenceViews.h"
#include "misTrackingSequenceHelper.h"
#include "ITrackerConfigure.h"

class igstkTracker;
class misTrackingToolQuery;
class misToolRepresentation;
class ITrackingTool;

class  misAscentionTrackingSubsequence : public misSubSequence,
	public ITrackingSubsequenceViews
{
public:
	misAscentionTrackingSubsequence(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		std::shared_ptr<ISubsequenceLayout> model,
	 std::shared_ptr<ITrackerConfigure> trackingConfig, std::shared_ptr<misSoftwareInformation> softwareInformation);

	virtual void InitialeGuiProcessing();
	void UpdateXYZView() override;
	void UpdateTopView(double * bound) override;
	void UpdateSideView(double * bound) override;
	void UpdateFrontView(double * bound) override;
	void UpdateStatus(long long int puls) override;
	bool ProcessRequest(misGUIEvent* pEvebt) override;
	void OnSelected();
	void TaskOnLeave();
	void ResetSetting();
	void Render();
	void AddTrackerTool(std::shared_ptr<ITrackingTool>  pTracker);
	void RealseAllResources() override;
	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>>	GetAllViewers() ;
	void DisconnectTracker();
 	bool ConnectToTracker();
	std::shared_ptr<misTrackingSequenceHelper> GetTrackerHelper() const override;

private:

	void UpdateViewOnCalibration();
 	bool ToolExistsInXMLlist(misToolPropertiesListTypdef xmlList, std::pair<ULONG, int> OneDetectedTool);
	void RefineListOfTools(misToolPropertiesListTypdef & xmlList, const std::map<ULONG, int> & DetectedTools);
	// assign  each tool to port specified by toolConfig
	void UpdateAscentionToolByPort(misToolConfiguration &toolConfig, misAscensionTracker * acension);
	void InitializeRenderingView() const;
	void MakeCameraAndFrustum();
	void SetStateToUnderGoing();

	std::shared_ptr<misSurfaceRepresentation>	CameraObject(std::string fileName);
	std::shared_ptr<ITrackerConfigure>	m_TrackingInitializer;
	std::shared_ptr<misTrackingSequenceHelper> m_TrackingViewHelper;
	misApplicationSetting* m_AppSetting;
	misTrackingStateReport m_LastRequiredToolInfo;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
};