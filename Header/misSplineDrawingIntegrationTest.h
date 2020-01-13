#pragma once
#include "misIntegrationTestTools.h"
#include "misIntegrationTestApplication.h"
#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misSplineDrawing.h"

class misSplineDrawingIntegrationTest : public misIntegrationTestApplication
{
public:
	misSplineDrawingIntegrationTest(int& argc, char** argv);
	virtual void PulseHandler();

private:
	void AddImage(std::string fileName, unsigned int serieIndex);
	void InitiVoreenShaders();
	void TranslatePlane();
	void TransformImagePlane();
	void SetModeToCaptureLandmark();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;
	vtkSmartPointer<misSplineDrawing> m_Spline;
};

