#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DViewer.h"
#include "IToolRepresentation.h"

// Test adding and updating view of landmarks
class misTorusToolRepTest :
	public misIntegrationTestApplication
{
public:
	misTorusToolRepTest(int &argc, char ** argv);

private:

	void SetupViewer();
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<I3DViewer>   m_Viewer;
	std::shared_ptr<IToolRepresentation> tool;
};

