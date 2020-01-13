#pragma once

#include "misSequenceManager.h"

class INavigationLayout;
class ITrackerImageSynchronizer;
class INavigationPackageFinder;
class ITreeViewUIUpdater;
class ICMFNavigationUIUpdater;
class IPackageDataVisualizer;
class INavigationTrackingHelper;
class IDatasetManager;
class IGeneralNavigationHelper;
class INavigationViewersNView;
class misCMFNavigationSubSequence;
class IViewerRepository;
class IViewerFactory;
class IGroupViewerFactory;

class misCMFNavigationSequence : public misSequenceManager
{
public:

	misCMFNavigationSequence(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IViewerRepository> viwerRepo,
		std::shared_ptr<IGroupViewerFactory> groupFactory,
		std::shared_ptr<IViewerFactory> viwerFactory, misStrctTabModel tabModel,
		std::shared_ptr<misSoftwareInformation> softwareInformation);

	std::shared_ptr<misCMFNavigationSubSequence> GetNavigationManager() { return this->m_NavigationSubSequence; };

	misCMFNavigationSequence(std::shared_ptr<INavigationLayout> layout,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<ICMFNavigationUIUpdater> navigationUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<ITrackerImageSynchronizer> toolSyncer,
		misStrctTabModel tabModel,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		const std::string& sequenceName = "CMFNavSeq",
		const std::string& subsequenceName = "CMFNavSubSeq");

	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();

protected:
	void InitilizeObject();

	std::shared_ptr<misCMFNavigationSubSequence> m_NavigationSubSequence;
};