#pragma once

class IGroupViewerSetting;
class INavigationViewersNView;
enum misApplicationType;

class INavigationLayout
{
public:
	virtual ~INavigationLayout() = default;

	virtual void UpdateLayoutToStandardsLayouts(
		bool freezState, misApplicationType appType, double VisibilityMarginInAnatomicalPlanesDirection) = 0;
	virtual void UpdateLayoutToDynamicLayout( 	bool freezState, misApplicationType appType, 
		const std::string& layoutType, double VisibilityMarginInAnatomicalPlanesDirection) = 0;
	virtual std::weak_ptr<INavigationViewersNView> GetGroupViwer() const = 0;
	virtual void SetDummyObject(itk::Object::Pointer forwarder) = 0;
	virtual bool IsIndynamicLayoutMode() const = 0;
};
