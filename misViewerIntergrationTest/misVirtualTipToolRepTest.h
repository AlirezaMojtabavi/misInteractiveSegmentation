#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DViewer.h"
#include "IToolRepresentation.h"

// Test adding and updating view of landmarks
class misVirtualTipToolRepTest :
	public misIntegrationTestApplication
{
public:
	misVirtualTipToolRepTest(int &argc, char ** argv);

private:

	void SetupViewer();
	void ObserveKeyEvent();

	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<I3DViewer>   m_Viewer;
	std::shared_ptr<IToolRepresentation> tool;
};