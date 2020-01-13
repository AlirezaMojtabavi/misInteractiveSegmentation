#pragma once
#include "mis3DViewer.h"
#include "misImage.h"

class misDICOMImageLoader;

//The class provide utilities for integration tests
class misIntegrationTestTools
{
public:
	misIntegrationTestTools(void);
	~misIntegrationTestTools(void);

	// Load image with with the specified name from from the (CurrentDir)/IMAGES/(imageName) subdirectory.
	std::shared_ptr<misImage> LoadImageData(const std::string& imageName, int seiIndex = 0);
	void CopyRawDicomImage();

	// InitializeRendering must be called RIGHT AFTER the VTK renderer is created (through creation of viewers). It shares the 
	// OpenGL contexts among viewers.
	static void InitializeRendering(std::vector<std::shared_ptr<I3DViewer>> viewers);

private:
	std::shared_ptr<misDICOMImageLoader> m_DicomImageLoader;
};

