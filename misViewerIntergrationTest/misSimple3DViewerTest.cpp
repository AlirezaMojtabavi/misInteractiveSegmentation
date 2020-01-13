#include "StdAfx.h"

#include "mis2DToolActor.h"
#include "misFrustumRepresentation.h"
#include "misSimple3DViewerTest.h"
#include "misWindow.h"
#include <mis3dAxisLandmark.h>
#include <misFileReader.h>

misSimple3DViewerTest::misSimple3DViewerTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv), m_Sphere(vtkSphereSource::New()),
	m_Sphere01(vtkSphereSource::New()), m_wnd(std::make_shared<misWindow>())
{
	
	this->m_wnd->set_m_Handle(GetMainWindow().Handle());
	this->m_wnd->GenerateRenderWindow(Iwindows::NoViewer);
	this->m_Viewer =  std::make_shared<mis3DViewer>(vtkPointPicker::New());
	this->m_Viewer->SetWindow(m_wnd, 0);
	this->m_wnd->GetRenderer(0)->SetBackground(0.2,1,1);
	auto frustum = std::make_shared<misFrustumRepresentation>("");
	m_Viewer->ShowFPSOn();
	m_Viewer->AddRepresentation(frustum);
	AddSTLs();
	auto dd = m_Viewer->GetRenderer()->GetActors();
}



void misSimple3DViewerTest::AddSphere() const
{
	
	m_Sphere->SetRadius(50);
	m_Sphere->SetThetaResolution(20);
	m_Sphere->SetPhiResolution(20);
	
	vtkPolyDataMapper* S_vtkMapper = vtkPolyDataMapper::New();
	S_vtkMapper->SetInputConnection(m_Sphere->GetOutputPort());
	mis2DToolActor* S_vtkActor = mis2DToolActor::New();
	S_vtkActor->SetMapper(S_vtkMapper);
	S_vtkActor->GetProperty()->SetColor(0, 1, 0);
	S_vtkActor->SetPosition(0, 0, 0);
	m_Viewer->GetRenderer()->AddActor(S_vtkActor);


	
}



void misSimple3DViewerTest::AddSTLs() const
{
	std::string filname = std::string("E:\\MIS-Solution\\misSolution_2010\\misSoloution\\CreateMISRelease_local\\FilesOfTrackers\\PolarisTrackerFiles\\Camera.STL");
	auto  polyData = misFileReader::ReadPolydataFromSTLFile(filname);
 

	auto   pCamera = std::make_shared<misSurfaceRepresentation>("camera");
	vtkProperty* prop = vtkProperty::New();
	prop->SetColor(0, 0, 1);
	pCamera->AddPolyData(polyData, prop);
	m_Viewer->AddRepresentation(pCamera);
}

 



 
void misSimple3DViewerTest::PulseHandler()
{
	m_Viewer->Render();
}
