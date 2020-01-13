
#include "misDICOMImageLoader.h"
#include "misVolumeSlicer.h"
#include "misIntegrationTestApplication.h"
#include "misWindow.h"
#include "misVolumeSlicer.h"

class misSplineIntgTest : public misIntegrationTestApplication
{
public:
	misSplineIntgTest(int &argc, char ** argv);


	virtual void PulseHandler();

private:
	void AddImage();
	void InitiVoreenShaders();
	void AddSplineWidget();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;
	misDICOMImageLoader* m_DICOMImageLoader;
	std::shared_ptr<misImage> m_Image;	
	std::shared_ptr<misPlanarRepresentation> mainRep;
};

