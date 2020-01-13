#pragma once

#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misIntegrationTestApplication.h"
#include "misWindow.h"
#include "vtkLineWidget2.h"
#include "misTextureEraser.h"

class misSegmentationWithBrush : public misIntegrationTestApplication
{
public:
	misSegmentationWithBrush(int &argc, char ** argv);
	void TranslatePlane();


	virtual void PulseHandler();

private:
	void AddImage();
	void InitiVoreenShaders();
	void UpdateTexture();
	void SetMouseCursor();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer> m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	std::shared_ptr<misImage> m_SegemntedImage;
	misOpenglTexture* imageTexure;
	int seriesNumber;
	std::string fileName;
	std::shared_ptr<misPlanarRepresentation> mainRep;
} ;
