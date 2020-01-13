#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misDICOMImageLoader.h"
#include "misCorrectionTransformBox.h"
#include "ITFILoader.h"
#include "mis3DVolumeRenderer.h"

class misMRICOlormapRenderingTest : public misIntegrationTestApplication
{
public:
	misMRICOlormapRenderingTest(int &argc, char ** argv);


	virtual void PulseHandler();

	void LoadTFIMap();

	
 
private:
	void InitiVoreenShaders();
	void AddVolume(std::string fileName, unsigned int serieIndex);

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>  m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	voreen::VoreenApplication* voreen;
	vtkSphereSource* m_Sphere;
	std::shared_ptr<ITFILoader> m_TFILoader1;
	misColorListTypedef   m_ColorList1;
	std::shared_ptr<ITFIAddressMapper> addressMapper;
};


