#include "stdafx.h"

#include "mis2DToolActor.h"
#include "misFrustumRepresentation.h"
#include "SimpleStickerActorViewerTest.h"
#include "misWindow.h"
#include "mis3dAxisLandmark.h"
#include "vtkLineSource.h"
#include "misTest\RandomDataGen.h"
#include "vtkVectorText.h"

SimpleStickerActorViewerTest::SimpleStickerActorViewerTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv), arrow(vtkConeSource::New()),
	m_Sphere01(vtkConeSource::New()), m_wnd(std::make_shared<misWindow>())
{
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::NoViewer);
	m_Viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	m_Viewer->SetWindow(m_wnd, 0);
	m_wnd->GetRenderer(0)->SetBackground(0.2, 1, 1);
	AddSphere();
}

void SimpleStickerActorViewerTest::AddSphere()
{
	arrow->SetRadius(5);
	arrow->SetResolution(10);
	arrow->SetHeight(50);
	auto cone = vtkSmartPointer<vtkConeSource>::New();

	cone->SetRadius(5);
	cone->SetResolution(10);
	cone->SetHeight(10);
	auto textSource = vtkSmartPointer<vtkVectorText>::New();
	textSource->SetText("Hello");

	m_StickerActor_second = vtkSmartPointer<vtkFollower>::New();
	m_StickerActor_text = vtkSmartPointer<vtkFollower>::New();

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	auto mapper_cone = vtkSmartPointer<vtkPolyDataMapper>::New();

	mapper->SetInputConnection(textSource->GetOutputPort());
	mapper_cone->SetInputConnection(cone->GetOutputPort());
	m_StickerActor_second->SetMapper(mapper_cone);
	m_StickerActor_text->SetMapper(mapper);
	m_Viewer->GetRenderer()->AddActor(m_StickerActor_second);
	m_Viewer->GetRenderer()->AddActor(m_StickerActor_text);
	m_StickerActor_second->SetCamera(m_Viewer->GetRenderer()->GetActiveCamera());
	m_StickerActor_text->SetCamera(m_Viewer->GetRenderer()->GetActiveCamera());
}

void SimpleStickerActorViewerTest::PulseHandler()
{
	auto transform = vtkSmartPointer<vtkTransform>::New();
	double translation[3];
	transform->Identity();
	transform->PostMultiply();
	m_StickerActor_second->SetUserMatrix(transform->GetMatrix());
	translation[0] = parcast::RandomDataGen::GenReal(0.0, 2.0);
	translation[1] = parcast::RandomDataGen::GenReal(0.0, 2.0);
	translation[2] = parcast::RandomDataGen::GenReal(0.0, 2.0);
	auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	auto camera = m_Viewer->GetRenderer()->GetActiveCamera();
	double worldRUPt[4];
	auto renderer = m_Viewer->GetRenderer();
	renderer->SetViewPoint(-0.8, 0.8, 0.2);
	renderer->ViewToWorld();
	renderer->GetWorldPoint(worldRUPt);

	if (worldRUPt[3])
	{
		worldRUPt[0] /= worldRUPt[3];
		worldRUPt[1] /= worldRUPt[3];
		worldRUPt[2] /= worldRUPt[3];
		worldRUPt[3] = 1.0;
	}
	transform->Translate(translation[0],
		translation[1],
		translation[2]);
	transform->Scale(0.01, 0.01, 0.01);
	transform->Translate(worldRUPt[0],
		worldRUPt[1],
		worldRUPt[2]);
	auto aa = transform->GetPosition();
	auto pp = transform->GetOrientation();
	m_StickerActor_second->SetUserMatrix(transform->GetMatrix());
	auto transformText = vtkSmartPointer<vtkTransform>::New();
	transformText->DeepCopy(transform);
	transformText->Translate(0, -0.2, 0);
	m_StickerActor_text->SetUserMatrix(transformText->GetMatrix());
	m_Viewer->Render();
}

void newStickerModelActor::GetMatrix(vtkMatrix4x4 *result)
{
	auto matrix = m_Renderer->GetActiveCamera()->GetViewTransformMatrix();
	Transform->Identity();
	Transform->SetMatrix(matrix);
	auto inverse = vtkMatrix4x4::New();
	auto transform = vtkSmartPointer<vtkTransform>::New();
	transform->GetInverse(inverse);
	Transform->PostMultiply();
	Transform->GetMatrix(result);
}