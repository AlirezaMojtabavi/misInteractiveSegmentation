#pragma once
#include "ICornerProperties.h"
#include "ICursorService.h"
#include "IScrewCompound.h"
class misScrewWidgetData;
class misPlanWidget;
class misScrewWidgetUpdateEvent;

namespace parcast
{
	class IScrewViewer
	{
	public:
		virtual ~IScrewViewer() = default;

		virtual bool ProcessUpdateScrewWidget(const misScrewWidgetUpdateEvent& screwWidgetUpdate,
		                               const std::shared_ptr<ICursorService>& cursorService) = 0;

		virtual void UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData) = 0;
		virtual std::shared_ptr<IScrewCompound> GetScrewWidgetService(misUID uid) = 0;
		virtual void SetAllScrewsLocked(bool isLocked) = 0;
		virtual void RemoveAllScrewServices() = 0;
		virtual void OnScrew(misUID screwUID) = 0;
		virtual void OnAllScrews() = 0;
		virtual void OffScrew(misUID screwUID) = 0;
		virtual void OffAllScrews() = 0;
		virtual void DeleteAllScrews() = 0;
		virtual void DeleteScrew(misUID screwUID) = 0;
		virtual void HighlightScrew(misUID screwUID, bool highlight) = 0;
		virtual void Clear() = 0;
		virtual void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) = 0;
	};
}

