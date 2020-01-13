#pragma once

#include "IDentalNavigationUIUpdater.h"

#include "misAutoCaptureScreenStrcts.h"
#include "mis3DModelViewingProperties.h"

class INavigationTrackingHelper;
class IGeneralNavigationHelper;

class misDentalNavigationUIUpdater : public IDentalNavigationUiUpdater
{
public:
	misDentalNavigationUIUpdater(const std::string& sequenceName, const std::string& subSequenceName,
		std::shared_ptr<IGeneralNavigationHelper> navHelper, std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		itk::Object* eventForwarder);
	void UpdateCurrentPackage(const misUID currentSelectedObjectPackageUid, const misUID imageUid) override;
	void UpdateStatus() override;
	void SetFreezState(bool val) override;

private:
	void UpdateAutomaticGotoFullScreenWindow();
	void UpdateNearestLandmarkInformation();
	void UpdateMeasurmentState();
	void UpdateCaptureScreenStatus();
	void UpdateVectorToTargetPoint();
	void UpdateToolsReport(void);
	void UpdateSnapShotTakerOnToolFixation(void);
	bool SendAppropriateToolMarkerVisibilityEvent();

	template <class EventType, typename PayloadType>
	void InvokeParentLoadedEvent(const PayloadType& payload)
	{
		EventType ev;
		ev.Set(payload);
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		m_ParentEventHandler->InvokeEvent(ev);
	}

	template <class EventType>
	void InvokeParentUnloadedEvent()
	{
		EventType ev;
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		m_ParentEventHandler->InvokeEvent(ev);
	}

	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<INavigationTrackingHelper> m_TrackingHelper;
	itk::Object::Pointer m_ParentEventHandler;
	const std::string m_SequenceName;
	const std::string m_SubsequenceName;

	double m_LastVectorToTargetPoint;
	bool m_FreezState;
	double m_AutomaticGotoFullScreenWindowValue;
	misCaptureScreenStatus m_CaptureStatus;
	double m_SnapshotTakerActionValue;
};

