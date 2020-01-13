#pragma once
#include "misIntegrationTestApplication.h"
#include "misDICOMImageLoader.h"
#include "mis3DVolumeRenderer.h"

// Test adding and updating view of landmarks
class mis3DlandMarkAddingTest : public misIntegrationTestApplication
{
public:
	mis3DlandMarkAddingTest(int &argc, char ** argv);
	void InitVolumeRendering();

private:
	void AddVolume();
 	std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(double* TableRange, misImageDataModality modality);
	float ConvertIntensityToKeyValue(const double* TableRange, double val);
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer> m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	voreen::VoreenApplication* voreen;

};

