#pragma once

#include "misSequenceManager.h"
#include "BiopsyToolTransformCalculator.h"
#include "IPlanEntryModifier.h"
#include "IAutomaticVirtualTipUpdater.h"
#include "IPlanNavigationVisualizer.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IBiopsyNavigationUiUpdater.h"
#include "misBiopsyNavigationSubSequence.h"

namespace parcast {
	class CustomizeArcTan;
}

class IViewerRepository;
class INavigationPackageFinder;
class IENTNavigationUIUpdater;
class IUserMessageBoardManager;
class IPackageDataVisualizer;
class INavigationTrackingHelper;
class IPlanningNavigation;
class IDatasetManager;
class IGeneralNavigationHelper;
class INavigationViewersNView;
class misBiopsyNavigationSubSequence;
class IViewerFactory;
class IGroupViewerFactory;
class ITreeViewUIUpdater;
class misTrackerImageSynchronizer;

using namespace parcast;

class misBiopsyNavigationSequence : public misSequenceManager
{
public:
	misBiopsyNavigationSequence(
		std::shared_ptr<IBiopsyToolTransformCalculatorNav> toolTransformCalculator,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		std::shared_ptr<IViewerRepository> viwerRepo,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGroupViewerFactory> groupFactory,
		std::shared_ptr<IViewerFactory> viwerFactory,
		misStrctTabModel tabModel,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		std::shared_ptr<IPlanEntryModifier> planEntryModifier,
		CustomizeArcTan expFunction,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier, std::shared_ptr<misSoftwareInformation> softwareInformation);

	misBiopsyNavigationSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IUserMessageBoardManager> messageBoard,
		std::shared_ptr<IBiopsyNavigationUiUpdater> navigationUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<misTrackerImageSynchronizer> toolSyncer,
		misStrctTabModel tabModel,
		CustomizeArcTan expFunction,
		std::unique_ptr<IAutomaticVirtualTipUpdater> automaticVirtualTipUpdater,
		std::shared_ptr<IUpdateLayoutToDynamicLayout> updateLayoutToDynamicLayout,
		std::shared_ptr<IUpdatePlaning> updatePlaning,
		std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
		std::shared_ptr<INavigationSubsequenceInitializer> navigationSubsequenceInitializer,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		const std::string& sequenceName = "BiopsyNavSeq",
		const std::string& subsequenceName = "BiopsyNavSubSeq");
	std::shared_ptr<misBiopsyNavigationSubSequence> GetNavigationManager();
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();
	void SetViewerRepo(std::shared_ptr<IViewerRepository> val);

protected:
	std::shared_ptr<misBiopsyNavigationSubSequence> m_NavigationSubSequence;
	void InitilizeObject();

};