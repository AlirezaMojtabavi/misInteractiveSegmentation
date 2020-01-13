#pragma once

#include "IDataCheckingUiUpdater.h"

namespace parcast
{

	class DataCheckingUiUpdater : public IDataCheckingUiUpdater
	{
	public:
		DataCheckingUiUpdater(
			const std::string& sequenceName,
			const std::string& subSequenceName,
			itk::Object* eventForwarder);
 		void SetVRThresholdSliderValue(double threshold) const override;
		void SelectImageInTreeView(int index) const override;
		void ShowLoadedSeri(std::vector< misImageViewingItemsStruct> imageList) const override;
		void OpenWaitingBar(const WaitingBarStringsStr& str) const override;
		void UpdateFaceInformation(const faceInformationListTypdef& faceInformationList) const override;
		void CloseWaitingbar() const override;
		void UpdateThreshold(const misSliderStrc& sliderRange) const override;
	private:
		template <class EventType, typename PayloadType>
		void InvokeLoadedEvent(const PayloadType& payload) const
		{
			EventType ev;
			ev.SetSequenceName(m_SequenceName);
			ev.SetSubTab(m_SubsequenceName);
			ev.Set(payload);
			m_ParentEventHandler->InvokeEvent(ev);
		}

		template <class EventType>
		void InvokeUnloadedEvent() const
		{
			EventType ev;
			ev.SetSequenceName(m_SequenceName);
			ev.SetSubTab(m_SubsequenceName);
			m_ParentEventHandler->InvokeEvent(ev);
		}
	private:
		itk::Object::Pointer m_ParentEventHandler;

		std::string m_SequenceName;
		std::string m_SubsequenceName;
	};

}
