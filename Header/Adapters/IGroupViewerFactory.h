#pragma once
#include "IPackageTransformUpdater.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ILandmarkViewerCollection.h"
#include "ICornerProperties.h"
#include "I3DViewer.h"
#include "IVolumeRenderer.h"

class IViewerFactory;
class ISubsequenceLayout;
class IGroupViewerSetting;
class INavigationViewersNView;
enum misApplicationType;

class IGroupViewerFactory
{
public:
 
	virtual std::shared_ptr<INavigationViewersNView> Create(std::shared_ptr<IGroupViewerSetting>,
		std::shared_ptr<ISubsequenceLayout> modelm, misApplicationType applicationType,
		std::shared_ptr<IViewerFactory> factory,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>, double visibiltyLandmarkOffset) = 0;
	virtual std::shared_ptr<ILandmarkViewerCollection> CreateLandmarkViewerCollection(std::shared_ptr<IGroupViewerSetting>,
		std::shared_ptr<ISubsequenceLayout> model, std::vector<std::shared_ptr<IVolumeRenderer>>  viewers, misApplicationType applicationType,
		std::shared_ptr<IViewerFactory> factory, 
		double visibiltyLandmarkOffset) = 0;
};
