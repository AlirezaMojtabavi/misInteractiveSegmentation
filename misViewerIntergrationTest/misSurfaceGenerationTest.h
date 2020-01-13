#pragma once
#include "misIntegrationTestApplication.h"
#include "misWindow.h"
#include "mis3DViewer.h"
#include "misDICOMImageLoader.h"
#include "misImage.h"
#include "mis3DVolumeRenderer.h"

// The misSurfaceGenerationTest generate and show iso surface 
class misSurfaceGenerationTest : public misIntegrationTestApplication
{
public:
	misSurfaceGenerationTest(int &argc, char ** argv);

private:
	void InitVolumeRendering();
	void AddSpineIsoSurface(char ** argv);
	void AddHeadIsoSurface(char** argv);

	void AddVolume();
	virtual void PulseHandler();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>  m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	char ** m_arg;
};

