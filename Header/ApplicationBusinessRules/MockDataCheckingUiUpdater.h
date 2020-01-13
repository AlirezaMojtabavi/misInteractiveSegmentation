#pragma once

#include "IDataCheckingUiUpdater.h"

MOCK_BASE_CLASS(MockDataCheckingUiUpdater, IDataCheckingUiUpdater)
{
	MOCK_CONST_METHOD(UpdateThresholdSlider, 1, void(const misSliderStrc& sliderRange));
	MOCK_CONST_METHOD(SetVRThresholdSliderValue, 1, void(double threshold));
	MOCK_CONST_METHOD(SelectImageInTreeView, 1, void(int index));
	MOCK_CONST_METHOD(ShowLoadedSeri, 1, void(std::vector<misImageViewingItemsStruct> imageList));
	MOCK_CONST_METHOD(OpenWaitingBar, 1, void(const WaitingBarStringsStr& str));
	MOCK_CONST_METHOD(UpdateFaceInformation, 1, void(const faceInformationListTypdef& faceInformationList));
	MOCK_CONST_METHOD(CloseWaitingbar, 0, void());
};
