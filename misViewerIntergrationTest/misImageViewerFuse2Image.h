#pragma once

#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misIntegrationTestApplication.h"
#include "misWindow.h"

class misImageViewerFuse2Image : public misIntegrationTestApplication
{
public:
	misImageViewerFuse2Image(int &argc, char ** argv);


	virtual void PulseHandler();
	
private:
	void AddImage();
	void InitiVoreenShaders();
	void TranslatePlane();
	void TransformImagePlane();	
	void SetModeToCaptureLandmark();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer>  m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image1, m_Image2;	
};

