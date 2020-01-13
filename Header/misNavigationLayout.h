#pragma once

#include "INavigationLayout.h"
#include "IOpenGLContextSharing.h"

class INavigationLayoutFactory;
class IViewerFactory;
class IGroupViewerSettingFinder;
class IGroupViewerFactory;
class ISubsequenceLayout;
class IViewerRepository;
class ITreeViewUIUpdater;
class IPackageDataVisualizer;
class IGeneralNavigationHelper;
class ITrackerImageSynchronizer;
class INavigationViewersNView;
class INavigationLayoutUiUpdater;
enum misApplicationType;

class misNavigationLayout : public INavigationLayout
{
public:
	misNavigationLayout(
		std::shared_ptr<IViewerRepository> viewerRepo,
		std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr<IGroupViewerFactory>,
		std::shared_ptr<INavigationLayoutFactory> factory,
		std::shared_ptr<IViewerFactory>,
		std::shared_ptr<INavigationLayoutUiUpdater> uiUpdater,
		std::shared_ptr<IGroupViewerSettingFinder> settingFinder,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ITrackerImageSynchronizer> toolSync,
		std::shared_ptr<IGeneralNavigationHelper> navigationHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> cSCorrelationManager,
		std::shared_ptr<ITreeViewUIUpdater> treeUiUpdater,
		std::shared_ptr<IOpenGLContextSharing> sharing,
		std::string sequenceName,
		std::string subsequenceName);
	void UpdateLayoutToStandardsLayouts(bool freezState, misApplicationType appType, double VisibilityMarginInAnatomicalPlanesDirection) override;
	void UpdateLayoutToDynamicLayout(bool freezState, misApplicationType appType,
		const std::string& layoutType, double VisibilityMarginInAnatomicalPlanesDirection) override;
	std::weak_ptr<INavigationViewersNView> GetGroupViwer() const override;
	void SetDummyObject(itk::Object::Pointer forwarder) override;



private:
	void ReInitilzeViewers(std::shared_ptr<IGroupViewerSetting> layout, 
		misApplicationType appType, 
		bool freezState, double VisibilityMarginInAnatomicalPlanesDirection);
	void UpdateZoomPercentage(int percentage, double proportion);

	bool m_LayoutMode = false;
	std::shared_ptr<INavigationLayoutUiUpdater> m_NavigationUIUpdater;
	std::string m_SequenceName;
	std::string m_SubsequenceName;
	std::shared_ptr<IGroupViewerSetting> m_DefaultLayout;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<ITreeViewUIUpdater> m_TreeViewUiUpdater;
	std::shared_ptr<IViewerRepository> m_ViewerRepo;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	bool IsIndynamicLayoutMode() const;

private:
	std::shared_ptr<INavigationLayoutFactory> m_LayoutFactory;
	std::shared_ptr<IGroupViewerFactory> m_GroupViewerFactory;
	std::shared_ptr<IGroupViewerSettingFinder> m_GroupViewerSettingFinder;
	std::shared_ptr<IViewerFactory> m_ViwerFactory;
	itk::Object::Pointer m_ParnetInvoker;
	std::shared_ptr<IOpenGLContextSharing> m_ContextSharing;
};

