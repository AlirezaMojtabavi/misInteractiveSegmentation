#pragma once
#include "misEnums.h"
#include "IGroupViewerFactory.h"
#include "IPackageTransformUpdater.h"

class misWindowModel;
class IGroupViewerSetting;
class ISubsequenceLayout;
class INavigationViewersNView;
class Iwindows;
class IViewerFactory;

class misGroupViewerFactory : public IGroupViewerFactory
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<Iwindows> CreateRenderingWindow(const misWindowModel& model);
	};

	misGroupViewerFactory(std::shared_ptr<Injector> injector = nullptr);
	std::shared_ptr<INavigationViewersNView> Create(std::shared_ptr<IGroupViewerSetting>,
		std::shared_ptr<ISubsequenceLayout> modelm, misApplicationType applicationType, 
		std::shared_ptr<IViewerFactory> factory, std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>, 
		double visibiltyLandmarkOffset) override;

private:
	std::shared_ptr<Injector>  m_Injector;
};

