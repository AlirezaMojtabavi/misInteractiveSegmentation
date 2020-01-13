#pragma once

#include "misSequenceManager.h"

class INavigationLayout;
class ITrackerImageSynchronizer;
class INavigationPackageFinder;
class ITreeViewUIUpdater;
class IENTNavigationUIUpdater;
class IPackageDataVisualizer;
class INavigationTrackingHelper;
class IDatasetManager;
class IGeneralNavigationHelper;
class INavigationViewersNView;
class misEntNavigationSubSequence;
class IViewerRepository;
class IViewerFactory;
class IGroupViewerFactory;

class misEntNavigationSequence : public misSequenceManager
{
public:

	misEntNavigationSequence(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IViewerRepository> viwerRepo,
		std::shared_ptr<IGroupViewerFactory> groupFactory,
		std::shared_ptr<IViewerFactory> viwerFactory, misStrctTabModel tabModel, std::shared_ptr<misSoftwareInformation> softwareInformation);

	std::shared_ptr<misEntNavigationSubSequence> GetNavigationManager() { return this->m_NavigationSubSequence; };

	misEntNavigationSequence(std::shared_ptr<INavigationLayout> layout,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IENTNavigationUIUpdater> navigationUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<ITrackerImageSynchronizer> toolSyncer,
		misStrctTabModel tabModel, std::shared_ptr<misSoftwareInformation> softwareInformation,
		const std::string& sequenceName = "ENTSpineNavSeq",
		const std::string& subsequenceName = "ENTSpineNavSubSeq");

	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();

protected:
	void InitilizeObject();

	std::shared_ptr<misEntNavigationSubSequence> m_NavigationSubSequence;
};