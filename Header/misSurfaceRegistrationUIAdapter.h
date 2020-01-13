#pragma once
#include "ISurfaceRegistrationUIAdapter.h"
#include "IUserMessageBoardManager.h"

class misSurfaceRegistrationUIAdapter : public ISurfaceRegistrationUIAdapter
{
public:
	misSurfaceRegistrationUIAdapter(itk::Object::Pointer eventForwarder, const std::string& sequenceName,
	                                const std::string& subSequenceName);

	template <class EventType, typename PayloadType>
	void InvokeParentLoadedEvent(const PayloadType& payload)
	{
		EventType ev;
		ev.Set(payload);
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		m_EventForwarder->InvokeEvent(ev);
	}

	template <class EventType>
	void InvokeParentUnloadedEvent()
	{
		EventType ev;
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		m_EventForwarder->InvokeEvent(ev);
	}

	void LandmarkRegistrationListUpdate(const std::vector<mislandMarkPosAndStatusStr>& landmarkList) override;
	void UpdateSurfaceRegistrationDataInGUI(const SurfaceRegistrationDataStrct& surfaceRegData, vtkPoints* capturePoints)
	override;
	void UpdateSurfaceRegistrationErrorResult(const SurfaceRegistrationDataStrct& surfaceRegData) override;
	void SetStatusMessage(const misTrackingStateReport& toolsStatus) override;

private:
	void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);


	itk::Object::Pointer m_EventForwarder;
	const std::string m_SequenceName;
	const std::string m_SubsequenceName;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	IUserMessageBoardManager::MessageId m_RegResultMsgId;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId;
	IUserMessageBoardManager::MessageId m_RegistrationResultMessage;
};

