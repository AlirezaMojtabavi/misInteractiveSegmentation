#pragma once
#include "misImageViewingItemsStruct.h"
#include "misGuiStructures.h"
#include "IVolumeThresholdUiUpdater.h"

struct misSliderStrc;
struct WaitingBarStringsStr;

namespace parcast
{

	class IDataCheckingUiUpdater : public IVolumeThresholdUiUpdater
	{
	public:
		virtual void SetVRThresholdSliderValue(double threshold) const = 0;
		virtual void SelectImageInTreeView(int index) const = 0;
		virtual void ShowLoadedSeri(std::vector<misImageViewingItemsStruct> imageList) const = 0;
		virtual void OpenWaitingBar(const WaitingBarStringsStr& str) const = 0;
		virtual void UpdateFaceInformation(const faceInformationListTypdef& faceInformationList) const = 0;
		virtual void CloseWaitingbar() const = 0;
	};

}
