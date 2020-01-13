#ifndef MISTRACKINGMANAGER_H_HEADER_INCLUDED_B7D53F72
#define MISTRACKINGMANAGER_H_HEADER_INCLUDED_B7D53F72

#include "ITrackingTool.h"
#include "mis3DViewer.h"
#include "misEventFromGui.h"
#include "misObject.h"
#include "misPolarisTracker.h"
#include "misSubSequence.h"
#include "misToolConfiguration.h"
#include "misTrackingStateReporter.h"
#include "misTrackingToolMarkerReporter.h"
#include "IMultiViewer.h"
#include "ITrackingSubsequenceViews.h"
#include "misTrackingSequenceHelper.h"
#include "IVolume3DRenderer.h"
#include "misMultiViewSubSequence.h"

class igstkTracker;
class misTrackingToolQuery;
class misToolRepresentation;
class ITrackingTool;


class  misPolarisTrackingSubsequence : public misSubSequence, public ITrackingSubsequenceViews
{
public:
	misPolarisTrackingSubsequence(std::shared_ptr<ISubsequenceLayout> model,
		 std::shared_ptr<ITrackerConfigure> trackingConfig,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, std::shared_ptr<misSoftwareInformation> softwareInformation);

	


	void MakeCameraFrustumPlaneForNDI();
	void UpdateXYZView() override;
	void UpdateTopView( double * bound ) override;
	void UpdateSideView( double * bound ) override;
	void UpdateFrontView( double * bound ) override;
	bool ProcessRequest(misGUIEvent* pEvebt) override;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() ;

	void OnSelected(void) override;
	void TaskOnLeave(void) override;
	misEventListTypedef	GetEventToGui() override;
	void ResetSetting(void) override;
	void Render() override;
	void UpdateStatus(long long int puls) override;
	void InitialeGuiProcessing();
	void AddTrackerTool(std::shared_ptr<ITrackingTool>  pTracker);
	void DisconnectTracker();
	virtual void RealseAllResources(void);
 	bool ConnectToTracker();
	virtual std::shared_ptr<misTrackingSequenceHelper> GetTrackerHelper() const override;
	

private:


	std::shared_ptr<misSurfaceRepresentation>	CameraObject(std::string fileName);
 	void	UpdateViewOnCalibration();
	tgt::dvec3 GetPolarisUpView();
	// Return up view based on local tracker coordinate system(Micron tracker developer manual (p13)(0, -1, 0))
	tgt::dvec3 GetMicronUpView();
	void InitializeRenderingView() const;
	void SetStateToUnderGoing();
	
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<ITrackerConfigure>	m_TrackingInitializer;
	std::shared_ptr<misTrackingSequenceHelper> m_TrackingViewHelper;
	misApplicationSetting* m_AppSetting;
	typedef igstk::NDICommandInterpreter CommandInterpreterType;
	misTrackingStateReport m_LastRequiredToolInfo;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;

};

#endif /* MISTRACKINGMANAGER_H_HEADER_INCLUDED_B7D53F72 */
