#include "StdAfx.h"

#include "misFrustumRepresentation.h"
#include "misIntegrationTestTools.h"
#include "Screw3DCompundIntgTest.h"
#include "misWin32Interactor.h"
#include "misWindow.h"
#include "vtkLineSource.h"
#include "vtkTubeFilter.h"
#include "misPlanSourceFactory.h"
#include "misInitializeScrewWidget.h"
#include "MedicalCameraDirection.h"

Screw3DCompundIntgTest::Screw3DCompundIntgTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv), m_wnd(std::make_shared<misWindow>())
{
	
	this->m_wnd->set_m_Handle(GetMainWindow().Handle());
	this->m_wnd->GenerateRenderWindow(Iwindows::VolumeViewer);
	auto viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	auto planSourceFactory = std::make_shared<misPlanSourceFactory>();
	auto appMode = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
	auto cornerProp = std::make_shared<misCornerProperties>(appMode);
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	auto screwServiceList = std::make_shared<ScrewListType>();

 	auto screwInitilize = std::make_unique<misInitializeScrewWidget>(screwServiceList, m_wnd->GetInterActor(),cornerProp, planSourceFactory, appMode,false );
	auto medicalDirection = std::make_shared<parcast::MedicalCameraDirection>(viewer);
	this->m_Viewer = std::make_shared<mis3DVolumeRenderer>(screwServiceList,m_wnd, 0, viewer, cornerProp, nullptr,std::move(screwInitilize), medicalDirection, nullptr);
	this->m_wnd->GetRenderer(0)->SetBackground(0.2,1,1);
 
	double pointStart[] = { 20, 20, 0 };
	double pointEnd[] = { 100, 100, 0 };
	misScrewWidgetData  data;
	data.SetEndPoint(pointEnd);
	data.SetScrewDiameter(5.0);
	data.SetStartPoint(pointStart);
	data.SetSourceType(Screw);
	m_Viewer->Render();
	m_Viewer->InitializeScrewWidget(data, IMAGEORIENTATION::UNKnownDirection);
	misAxisProperty  axis(100, 100, 100);
	axis.SetGeoType(misAxisProperty::line);
	viewer->AddAxis(axis);
	

}

void Screw3DCompundIntgTest::PulseHandler()
{
	m_Viewer->Render();
}
