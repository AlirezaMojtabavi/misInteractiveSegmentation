#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DVolumeRenderer.h"

// Test adding and updating view of landmarks
class Screw3DCompundIntgTest :
	public misIntegrationTestApplication
{
public:
	Screw3DCompundIntgTest(int &argc, char ** argv);
	void InitVolumeRendering();
	virtual void PulseHandler();
private:
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
};

