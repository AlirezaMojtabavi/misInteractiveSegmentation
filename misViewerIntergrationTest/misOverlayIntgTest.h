#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DViewer.h"

// Test adding and updating view of landmarks
class misOverlayIntgTest :
	public misIntegrationTestApplication
{
public:
	misOverlayIntgTest(int &argc, char ** argv);

	void InitVolumeRendering();
	virtual void PulseHandler();
private:
	void AddOverlaySphere() ;
	void AddSphere();
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<I3DViewer>   m_Viewer;
};

