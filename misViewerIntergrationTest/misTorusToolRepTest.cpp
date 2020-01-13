#include "StdAfx.h"
#include "misTorusToolRepTest.h"
 #include "misToolRepresentation.h"
#include "misToolShapeBuilder.h"
#include "misWindow.h"


misTorusToolRepTest::misTorusToolRepTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv), m_wnd(std::make_shared<misWindow>())
{
	SetupViewer();
 
}


void misTorusToolRepTest::SetupViewer()
{
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::NoViewer);
	m_Viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	m_Viewer->SetWindow(m_wnd, 0);
	m_wnd->GetRenderer(0)->SetBackground(0.2, 1, 1);
	misToolShapeBuilder toolSahepBuilder(Biopsy);

	misToolProperties toolProp;
	toolSahepBuilder.SetToolRepresentationParam(SpatialObj2D, toolProp, false);
	tool = toolSahepBuilder.GetToolRepresentation();
	tool->SetTorusVisibility(true);
	tool->SetVisibilityOn();
	m_Viewer->AddRepresentation(tool->GetSurface());
}





