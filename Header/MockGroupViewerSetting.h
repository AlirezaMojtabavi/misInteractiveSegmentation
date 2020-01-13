#pragma once

#include "IGroupViewerSetting.h"

MOCK_BASE_CLASS(MockGroupViewerSetting, IGroupViewerSetting)
{
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(SetLandmarkExisted, 1, void(bool pVal));
	MOCK_NON_CONST_METHOD(SetMainWidgetType, 1, void(misCursorType pCursorType));
	MOCK_NON_CONST_METHOD(SetVolumeViewingType, 1, void(misVolumeViewingTypes pVolumeViewingType));
	MOCK_NON_CONST_METHOD(GetNumberOfViewers, 0, int());
	MOCK_NON_CONST_METHOD(GetTypeOfViewer, 1, misViewerTypeDirection(int pElement));
	MOCK_NON_CONST_METHOD(GetVolumeViewingType, 0, misVolumeViewingTypes());
	MOCK_NON_CONST_METHOD(GetPlaneVisibilityStatus, 1, MapType(int));
	MOCK_NON_CONST_METHOD(GetMainWidgetType, 0, misCursorType());
	MOCK_NON_CONST_METHOD(GetSurgeryType, 0, misSurgeryType());
	MOCK_NON_CONST_METHOD(GetOrientation, 1, IMAGEORIENTATION(int pElement));
	MOCK_NON_CONST_METHOD(GetKeepColor, 0, bool(), identifier_1);
	MOCK_NON_CONST_METHOD(SetKeepColor, 1, void(bool val));
	MOCK_NON_CONST_METHOD(GetViewPort, 2, misViewPort(int groupIndex, int subIndex));
	MOCK_NON_CONST_METHOD(AddWindowGroup, 1, void(const misViewElementGroup&));
	MOCK_CONST_METHOD(GetElement, 1, const misViewElementGroup&(int index));
	MOCK_CONST_METHOD(GetNumberOfGroupElement, 0, int());
	MOCK_NON_CONST_METHOD(FindDistributionMap, 1, misDistributionMap*(const itk::EventObject*  pEvent));
	MOCK_NON_CONST_METHOD(SetAllMapTo, 2, void(const itk::EventObject*  pEvent, bool val));
	MOCK_NON_CONST_METHOD(SetElementTo, 4, void(const itk::EventObject*  pEvent, int i, int j, bool val));
	MOCK_NON_CONST_METHOD(SetAllElemetsToDefault, 1, void(const itk::EventObject*  pEvent));
	MOCK_NON_CONST_METHOD(GetWindowsLayout, 0, misWindowsLayout());
	MOCK_CONST_METHOD(serialize, 1, void(XmlSerializer& s));
	MOCK_NON_CONST_METHOD(deserialize, 1, void(XmlDeserializer& s));

	MOCK_NON_CONST_METHOD(SetWidgetLineWidth, 1, void(const double ));
	MOCK_NON_CONST_METHOD(SetWidgetColorComposition, 1, void(const parcast::AxesColors& colors));

	MOCK_CONST_METHOD(GetWidgetColorComposition, 0, parcast::AxesColors());
	MOCK_CONST_METHOD(GetWidgetLineWidth, 0, double());
	

};