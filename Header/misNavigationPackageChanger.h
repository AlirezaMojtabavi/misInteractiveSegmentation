#pragma once
#include "INavigationPackageChanger.h"
#include "IPackageDataVisualizer.h"
#include "IGeneralNavigationHelper.h"
#include "ITrackerImageSynchronizer.h"
#include "INavigationLayout.h"
#include "IUpdateLayoutToDynamicLayout.h"
#include "INavigationLayoutUiUpdater.h"
#include "../misNavigationSubsequenceIntegrationTest/FakeNavigationUIUpdater.h"
#include "IVolumeCropping.h"

class misNavigationPackageChanger :
	public INavigationPackageChanger
{
public:
	misNavigationPackageChanger(std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
	                            std::shared_ptr<IGeneralNavigationHelper> generalNavigationHelper,
		std::shared_ptr<ITrackerImageSynchronizer> toolSync, 
				std::shared_ptr<INavigationLayout> navigationLayout, 
		std::shared_ptr<INavigationUIUpdater>, std::shared_ptr<IUpdateLayoutToDynamicLayout> updateLayoutToDynamicLayout, std::shared_ptr<IVolumeCropping>);
	void ChangePackage(std::shared_ptr<INavigationViewersNView> groupViewer, const std::string&  newPackageUID, const std::string& selectedLayout,
	                   double VisibilityMarginInAnatomicalPlanesDirection, bool freezeState) override;
	void UpdateLayoutListInUI(std::shared_ptr<ISimpleDataPackage> package);
 private:
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<INavigationLayout> m_NavigationLayout;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IUpdateLayoutToDynamicLayout> m_UpdateLayoutToDynamicLayout;
	std::shared_ptr<INavigationUIUpdater> m_NavigationUIUpdater;
	std::shared_ptr<IVolumeCropping> m_VolumeCropper;

};

