
#pragma once

#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misIntegrationTestApplication.h"
#include "misWindow.h"
#include "vtkLineWidget2.h"

class misImageViewerLandMarkVisibilityTest : public misIntegrationTestApplication
{
public:
	misImageViewerLandMarkVisibilityTest(int &argc, char ** argv);

	void AddSphere() const;


	virtual void PulseHandler();

private:
	void AddImage();
	void InitiVoreenShaders();
	void SetModeToCaptureLandmark();
	

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer> m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	vtkRenderer* refernceCheck;
	misOpenglTexture* imageTexure;
	int seriesNumber;
	std::string fileName;
	vtkSmartPointer< vtkLineWidget2 > widget;
};


