#pragma once

class INavigationViewersNView;

class ITreeViewUIUpdater
{
public:
	virtual void UpdateImageSettingPanelPropertiesGUI() = 0;
	virtual void Update3DModelSettingPanelPropertiesGUI() = 0;
	virtual void SetNavigationNView(std::weak_ptr<INavigationViewersNView> val) = 0;
	virtual void SetDummyObject(itk::Object::Pointer forwarder) = 0;
};