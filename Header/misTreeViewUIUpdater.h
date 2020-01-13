#pragma once
#include "ApproachAndModelInformationStrct.h"
#include "IPackageDataVisualizer.h"
#include "ITreeViewUIUpdater.h"

class misTreeViewUIUpdater : public ITreeViewUIUpdater
{
public:
	misTreeViewUIUpdater(std::shared_ptr<IPackageDataVisualizer> packageVisualizer, 
		std::weak_ptr<INavigationViewersNView> navigationNView,
			std::string sequenceName,
	std::string subsequenceName);
	void UpdateImageSettingPanelPropertiesGUI() override;
	void Update3DModelSettingPanelPropertiesGUI() override;
 	void SetNavigationNView(std::weak_ptr<INavigationViewersNView> val) override;
	void SetDummyObject(itk::Object::Pointer forwarder);
private:
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::weak_ptr<INavigationViewersNView> m_NavigationNView;
	std::weak_ptr<ISimpleDataPackage> m_CurrentPackage;	// a pointer to package you are working with
	std::string m_SequenceName;
	std::string m_SubsequenceName;
	itk::Object::Pointer m_ParentEventHandler;

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


};

