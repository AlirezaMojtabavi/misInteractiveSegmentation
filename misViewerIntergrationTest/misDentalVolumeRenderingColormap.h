#pragma once
#include <misImage.h>
#include "../misIntegrationDataBaseTests/misLoadAndShowPackageTest.h"
#include "misDICOMImageLoader.h"
#include "mis3DVolumeRenderer.h"


class misDentalVolumeRenderingColormap : public misIntegrationTestApplication
{
public:
	misDentalVolumeRenderingColormap(int &argc, char ** argv);
	virtual void PulseHandler();

private:

	void InitiVoreenShaders();
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;	
	void AddVolume();

};



