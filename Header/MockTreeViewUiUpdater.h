#pragma once

#include "ITreeViewUIUpdater.h"

MOCK_BASE_CLASS(MockTreeViewUIUpdater, ITreeViewUIUpdater)
{
	MOCK_NON_CONST_METHOD(UpdateImageSettingPanelPropertiesGUI, 0, void());
	MOCK_NON_CONST_METHOD(Update3DModelSettingPanelPropertiesGUI, 0, void());
	MOCK_NON_CONST_METHOD(SetNavigationNView, 1, void(std::weak_ptr<INavigationViewersNView> val));
	MOCK_NON_CONST_METHOD(SetDummyObject, 1, void(itk::Object::Pointer forwarder));
};