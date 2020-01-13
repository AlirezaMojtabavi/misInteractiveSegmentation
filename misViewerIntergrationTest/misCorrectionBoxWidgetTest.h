#pragma once
#include "mis3DViewer.h"
#include "misCorrectionTransformBox.h"
#include "misIntegrationTestApplication.h"

// Test adding and updating view of landmarks
class misCorrectionBoxWidgetTest :	public misIntegrationTestApplication
{
public:
	misCorrectionBoxWidgetTest(int &argc, char ** argv);
	void InitVolumeRendering();
	virtual void PulseHandler();
private:
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<I3DViewer>   m_Viewer;
	misCorrectionTransformBox  m_Box;
	misFaceInformation m_FaceInformation1st;
	misFaceInformation m_FaceInformation2nd;
	faceInformationListTypdef m_FaceInformationApplied;
};

