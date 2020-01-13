#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misPackage3DDataRenderingAdapter.h"
#include "ITFILoader.h"


// Create simple package and show default volume
class misSimplePackageViewerTest : public misIntegrationTestApplication
{
public:
	misSimplePackageViewerTest(int &argc, char ** argv);
    std::shared_ptr<ITFILoader> GetTFILoader() const { return m_TFILoader1; }
private:
	// Initialize voreen singletons
	void InitVoreenShaders();
	void SetColorList(misColorListTypedef val) { m_ColorList1 = val; }
	void LoadTFIMap();

	void PulseHandler();
	// Load an image and create a simple package
	void AddPackage(char ** argv);

	std::shared_ptr<misPackage3DDataRenderingAdapter> m_Viewer;
	std::shared_ptr<misSimpleDataPackage> m_Package;
	std::shared_ptr<ITFILoader> m_TFILoader1;
	misColorListTypedef   m_ColorList1;
	std::shared_ptr<IImage> m_Image;
	double m_CurrentThreshold;
};


