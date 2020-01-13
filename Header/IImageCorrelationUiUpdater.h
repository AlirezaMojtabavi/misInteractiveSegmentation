#pragma once
#include "misCoreEvents.h"

enum class ProgressBarStatus;

namespace parcast
{

	class IImageCorrelationUiUpdater
	{
	public:
		virtual ~IImageCorrelationUiUpdater() = default;
		virtual void UpdateIsPackageAcceptedFlag(bool IsCalculateButtonClicked) const = 0;
		virtual void UpdateAutoCorrelationProgress(unsigned int currentIteration, unsigned int totalIteration, bool resetCorrelation) = 0;
		virtual void UpdateAutoCorrelationProgressBarState(ProgressBarStatus value) const = 0;
		virtual void UpdateAutoCorrelationProgressBarValue(double value) const = 0;
		virtual void ShowLoadedSeri(const std::vector<ImageViewingCorrelationStruct>& imageCorrelationList) const = 0;
		virtual void ShowWarning(const misCorrelationWarningState& state) const = 0;
		virtual void ResetUids() const = 0;
		virtual void StartProgressBar(const std::string& title, const std::string& status) const = 0;
		virtual void StopProgressBar() const = 0;
		virtual void SetSelectedImage(int index) const = 0;
		virtual void ShowLandmarks(const misPairLandMarkStatusListType& landmarkList) const = 0;
		virtual void ChangeStateButton() const = 0;
	};

}
