#pragma once
#include "INavigationSubsequneInitilizer.h"
#include "../misDataBaseIoIntgTest/DatabaseEndToEndTestSteps.h"
#include <boost/container/container_fwd.hpp>
#include "IGeneralNavigationHelper.h"
#include "IShowCurrentPackage.h"
#include "INavigationLayoutUiUpdater.h"
#include "../misNavigationSubsequenceIntegrationTest/FakeNavigationUIUpdater.h"

class misNavigationSubsequenceInitializer : public INavigationSubsequenceInitializer
{
public:
	misNavigationSubsequenceInitializer(std::shared_ptr<INavigationUIUpdater> navigationUIUpdater,
	std::shared_ptr<IGeneralNavigationHelper> generalNavigationHelper,
	std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
	std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
	std::shared_ptr<INavigationViewersNView> groupViewer);
	void Start(std::shared_ptr<ISimpleDataPackage> currentPackage, bool freezeState) override;
private:

	void UploadAllTextures(ImageListTypedef images);
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<INavigationUIUpdater> m_NavigationUIUpdater;
	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<IShowCurrentPackage> m_ShowCurrentPackage;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;

};

