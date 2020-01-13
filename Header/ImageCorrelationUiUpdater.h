#pragma once
#include "IImageCorrelationUiUpdater.h"

namespace parcast
{

	class ImageCorrelationUiUpdater : public IImageCorrelationUiUpdater
	{
	public:
		ImageCorrelationUiUpdater(
			const std::string& sequenceName,
			const std::string& subSequenceName,
			itk::Object* eventForwarder);

		void UpdateIsPackageAcceptedFlag(bool IsCalculateButtonClicked) const override;
		void UpdateAutoCorrelationProgressBarState(ProgressBarStatus value) const override;
		virtual void UpdateAutoCorrelationProgressBarValue(double value) const override;
		void UpdateAutoCorrelationProgress(unsigned int currentIteration, unsigned int totalIteration, bool resetCorrelation) override;
		void ShowLoadedSeri(const std::vector<ImageViewingCorrelationStruct>& imageCorrelationList) const override;
		void ShowWarning(const misCorrelationWarningState& state) const override;
		void ResetUids() const override;
		void StartProgressBar(const std::string& title, const std::string& status) const override;
		void StopProgressBar() const override;
		void SetSelectedImage(int index) const override;
		void ShowLandmarks(const misPairLandMarkStatusListType& landmarkList) const override;
		void ChangeStateButton() const override;

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
 
 
		itk::Object::Pointer m_ParentEventHandler;

		std::string m_SequenceName;
		std::string m_SubsequenceName;
		ProgressBarStatus m_ProgressBarStatus = ProgressBarStatus::NotStarted;
	};

}
