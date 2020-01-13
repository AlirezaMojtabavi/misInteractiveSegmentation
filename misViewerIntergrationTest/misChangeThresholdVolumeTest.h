#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misPackage3DDataRenderingAdapter.h"


// Create simple package and show default volume
class misChangeThresholdVolumeTest : public misIntegrationTestApplication
{
public:
	misChangeThresholdVolumeTest(int &argc, char ** argv);

private:
	// Initialize voreen singletons
	void InitVoreenShaders();

	// Load an image and create a simple package
	void AddPackage();

	virtual void PulseHandler();

	std::shared_ptr<misPackage3DDataRenderingAdapter> m_Viewer; 
	std::shared_ptr<misImage> m_Image;
	std::shared_ptr<misSimpleDataPackage> m_Package;
};


