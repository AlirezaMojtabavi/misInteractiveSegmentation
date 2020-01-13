#pragma once
#include "INavigationLayout.h"

MOCK_BASE_CLASS(MockNavigationLayout, INavigationLayout)
{
	MOCK_NON_CONST_METHOD(UpdateLayoutToStandardsLayouts, 3, void(bool freezState, misApplicationType appType, double VisibilityMarginInAnatomicalPlanesDirection));
	MOCK_NON_CONST_METHOD(UpdateLayoutToDynamicLayout, 4, void(bool freezState, misApplicationType appType,
		const std::string& layoutType, double VisibilityMarginInAnatomicalPlanesDirection));
	MOCK_CONST_METHOD(GetGroupViwer, 0, std::weak_ptr<INavigationViewersNView>());
	MOCK_NON_CONST_METHOD(SetDummyObject, 1, void(itk::Object::Pointer forwarder));
	MOCK_CONST_METHOD(IsIndynamicLayoutMode, 0, bool());
};
