#pragma once
#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misIntegrationTestApplication.h"
#include "misWindow.h"

// The misColoredImageRenderingTest class used for test rendering 3 - component image
class misColoredImageRenderingTest : public misIntegrationTestApplication
{
public:
	misColoredImageRenderingTest(int &argc, char ** argv);

	virtual void PulseHandler();

private:

	// Build a 2d representation for rendering 3d image
	void InitializeRendering();

	// Generate a 3 component image
	vtkImageData* GenerateFakeColoredImage();
	
	// Init voreen singletons(shader manager)
	void InitiVoreenShaders();
	
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer> m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
};

