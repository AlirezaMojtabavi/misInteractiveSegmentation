#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DVolumeRenderer.h"
#include "misDICOMImageLoader.h"

class misNew3DlandmarkAddingTest :	public misIntegrationTestApplication
{
public:
	misNew3DlandmarkAddingTest(int &argc, char ** argv);
	void InitVolumeRendering();
	~misNew3DlandmarkAddingTest();
private:
	void AddVolume(char** argv);
	std::shared_ptr<TransFuncIntensity> GenerateTransferFunction(double* TableRange, misImageDataModality modality);
	float ConvertIntensityToKeyValue(const double* TableRange, double val);
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
};



