#pragma once
#include "IScrewViewer.h"
#include "IInitializeScrewWidget.h"
#include "misVolumeRendererContainer.h"


class ScrewViewer : public IScrewViewer
{
public:
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	ScrewViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
	            std::shared_ptr<ScrewListType> screwServiceList,
	            std::shared_ptr<ICornerProperties> cornerproperties,
	            misVolumeRendererContainer::Pointer parent);
	~ScrewViewer();

	bool ProcessUpdateScrewWidget(const misScrewWidgetUpdateEvent& screwWidgetUpdate,
	                              const std::shared_ptr<ICursorService>& cursorService) override;
	void UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData) override;
	std::shared_ptr<IScrewCompound> GetScrewWidgetService(misUID uid) override;
	void SetAllScrewsLocked(bool isLocked) override;
	void RemoveAllScrewServices() override;
	void OnScrew(misUID screwUID) override;
	void OffScrew(misUID screwUID) override;
	void DeleteAllScrews() override;
	void DeleteScrew(misUID screwUID) override;
	void HighlightScrew(misUID screwUID, bool highlight) override;
	void Clear() override;
	void OnAllScrews() override;
	void OffAllScrews() override;
protected:
	void ModifyPlane(misPlanWidget* planWidget, misScrewWidgetData& screwWidgetVal);
	void InvokeEvent(const itk::EventObject& event);

 

protected:
	std::shared_ptr<IInitializeScrewWidget> m_InitializeScrewWidget;
	std::shared_ptr<ScrewListType> m_ScrewServiceList;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	misVolumeRendererContainer::Pointer m_Parent;
};
