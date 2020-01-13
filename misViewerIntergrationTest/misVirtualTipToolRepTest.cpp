#include "StdAfx.h"
#include "misVirtualTipToolRepTest.h"
#include "misWin32Interactor.h"
#include "misToolRepresentation.h"
#include "misToolShapeBuilder.h"
#include "misWindow.h"

class misVPObserver : public vtkCommand
{
private:
	double length;

public:
	std::shared_ptr<IToolRepresentation> tool;
	misVPObserver()
		:length(0.0), tool(nullptr)
	{

	}
	static misVPObserver  *New()
	{
		return new misVPObserver;
	}

	void  Execute(vtkObject *caller, unsigned long eventId, void *callData)
	{
		auto winInteractor = dynamic_cast<vtkRenderWindowInteractor *>(caller);
		if (winInteractor->GetKeyCode() == 'l')
		{
			length = length + 0.2;
			tool->SetVirtualTipLength(length);
		}
	}
};

misVirtualTipToolRepTest::misVirtualTipToolRepTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv)
{
	SetupViewer();
	ObserveKeyEvent();
	m_wnd = std::make_shared<misWindow>();
}

void misVirtualTipToolRepTest::SetupViewer()
{
	m_wnd = std::make_shared<misWindow>();
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::NoViewer);
	m_Viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	m_Viewer->SetWindow(m_wnd, 0);
	m_wnd->GetRenderer(0)->SetBackground(0.2, 1, 1);
	misToolShapeBuilder toolSahepBuilder(Spine);
	misToolProperties toolProp;
	toolSahepBuilder.SetToolRepresentationParam(SpatialObj2D, toolProp, false);
	tool = toolSahepBuilder.GetToolRepresentation();
	tool->SetVirtualTipLength(20.0);
	tool->SetVisibilityOn();
	m_Viewer->AddRepresentation(tool->GetSurface());
}

void misVirtualTipToolRepTest::ObserveKeyEvent()
{
	auto wndInteractor = m_wnd->GetInterActor();
	auto keyObserver = misVPObserver::New();
	keyObserver->tool = tool;
	wndInteractor->AddObserver(vtkCommand::KeyPressEvent, keyObserver, 0);
}