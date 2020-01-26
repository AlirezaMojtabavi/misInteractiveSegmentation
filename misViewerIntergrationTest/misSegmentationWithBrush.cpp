#include "stdafx.h"
#include "misSegmentationWithBrush.h"

#include "misEnumUtilities.h"
#include "misPlanarRepresentation.h"
#include "misImageToTextureMap.h"
#include "misIntegrationTestTools.h"
#include "misTest\RandomDataGen.h"
#include "ICursorService.h"
#include "misImageSlicerMapper.h"
#include "misApplicationSetting.h"
#include "vtkLineRepresentation.h"
#include "PointSelectAction.h"
#include "BackToPanMode.h"
#include "misCursorService.h"
#include "resource.h"
#include "BrushImageGeneration.h"
#include <misDatasetIO.h>
#include "../Header/SlicerPointSelectAction.h"
using namespace std;

misSegmentationWithBrush::misSegmentationWithBrush(int &argc, char ** argv)
	: misIntegrationTestApplication(argc, argv), m_wnd(std::make_shared<misWindow>())
{
	vtkObject::GlobalWarningDisplayOff();

	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->SetProvidedWindowAsParent(false);
	m_wnd->GenerateRenderWindow(Iwindows::NoViewer);

	std::shared_ptr<I3DViewer> viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	viewer->SetWindow(m_wnd, 0);
	auto screwList = std::make_shared<misVolumeSlicer::ScrewListType>();
	auto interactorStyleImageExtend = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	auto corner = std::make_shared<misCornerProperties>(misApplicationSetting::GetInstance()->m_WorkflowButtonSet);
	auto measureMent = misMeasurment::New();
	auto dummy = misVolumeRendererContainer::New();
	auto cursorService = std::make_shared<misCursorService>();
	auto imageStyle = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	auto backToPan = std::make_shared<BackToPanMode>(measureMent, imageStyle, viewer, dummy);

	//m_Viewer = std::make_shared<misVolumeSlicer>(screwList, m_wnd, 0, viewer, corner, nullptr, nullptr,
	//	interactorStyleImageExtend, measureMent, dummy, cursorService, backToPan, 7, std::make_shared<LandmarkDataAndType>());
	m_wnd->GetRenderer(0)->SetBackground(0.2, 1, 1);
	m_Viewer->Render();
	InitiVoreenShaders();
	fileName = argv[1];
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_Image->Update();
	m_SegemntedImage = testTools.LoadImageData(argv[1], seriesNumber);
	m_SegemntedImage->Update();
	auto segementationIMage = m_SegemntedImage->GetRawImageData();
	auto tabklerange1 = m_SegemntedImage->GetRawImageData()->GetScalarRange();
	int* dims = m_Image->GetDimensions();
	short* pointerImage = (short*)segementationIMage->GetScalarPointer();
	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
				pointerImage[z*(dims[1] * dims[0]) + y * dims[0] + x] = -1000;
	//segementationIMage->Modified();
	auto tabklerange2 = m_SegemntedImage->GetRawImageData()->GetScalarRange();
	m_SegemntedImage->Modified();
	auto pan = std::make_shared<BackToPanMode>(measureMent, interactorStyleImageExtend, viewer, dummy);

	//auto pointSelectCallBack = new PointSelectAction(viewer, m_Viewer, corner, interactorStyleImageExtend, pan, dummy,
	//	cursorService, m_Viewer->GetCameraService(),
	//	std::make_shared<LandmarkDataAndType>());
	//auto pairEvent = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(vtkCommand::LeftButtonPressEvent, pointSelectCallBack);
	//auto pairEvent2 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(vtkCommand::RightButtonPressEvent, pointSelectCallBack);
	//m_Viewer->AddPointSelectObserver(pairEvent);
	//m_Viewer->AddPointSelectObserver(pairEvent2);

	auto pointSelectCallBack = vtkSmartPointer<SlicerPointSelectAction>::New();
	pointSelectCallBack->Create(viewer, m_Viewer, corner, interactorStyleImageExtend, pan, dummy,
		cursorService, m_Viewer->GetCameraService());
	brushObserver = vtkSmartPointer<BrushImageGeneration>::New();
	brushObserver->Create(viewer, m_Viewer, corner, dummy, cursorService, m_Viewer->GetCameraService());
	auto pairEvent3 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(vtkCommand::MouseMoveEvent, brushObserver);
	auto pairEvent4 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(vtkCommand::LeftButtonPressEvent, brushObserver);
	auto pairEvent5 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(vtkCommand::LeftButtonReleaseEvent, brushObserver);
	m_Viewer->AddPointSelectObserver(pairEvent3);
	m_Viewer->AddPointSelectObserver(pairEvent4);
	m_Viewer->AddPointSelectObserver(pairEvent5);
	AddImage();
	//brushObserver->CreateTExture();
}

void misSegmentationWithBrush::TranslatePlane()
{

	auto center = m_Image->GetImageCenter();
	auto pTransform = vtkSmartPointer<vtkTransform>::New();
	pTransform->PostMultiply();
	pTransform->Translate(center.Elements());
	m_Viewer->GetCornerProperties()->SetMatrix(pTransform->GetMatrix());
	m_Viewer->UpdateImage();

}

void misSegmentationWithBrush::AddImage()
{

	if (m_Viewer)
	{
		string RepType = misEnumUtilities::ConvertImageOrientationTypeEnumToString(CORONAL, ENT);
		auto sliceMapper = new misImageSlicerMapper(CORONAL);
		mainRep = std::make_shared<misPlanarRepresentation>(RepType, sliceMapper);
		m_Viewer->SetMainRepresentation(mainRep, CORONAL);
		m_Viewer->InitializeCornerProperties();
		m_Viewer->GetCursorService()->SetImageOrientation(CORONAL);
	}

	m_Viewer->SetObliqueFlag(false);
	UpdateTexture();
	m_Viewer->AddRepresentation(mainRep);
	TranslatePlane();
	m_Viewer->Render();
}

void misSegmentationWithBrush::InitiVoreenShaders()
{
	auto basePath_ = FileSystem::currentDirectory();
	auto shaderPath_ = basePath_ + "/glsl";
	tgt::ShaderManager* shdrmgr = Singleton<tgt::ShaderManager>::GetInstance();
	shdrmgr->addPath(shaderPath_);


	voreen::VoreenApplication* m_Voreen = new voreen::VoreenApplication();
	m_Voreen->init();
	m_Voreen->initGL();
	glewInit();
}


void misSegmentationWithBrush::UpdateTexture()
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	imageTexure = TextureHandler->LookUpTexture(m_Image);
	mainRep->SetImageSource(m_Image, FirstImage, MainImage);
	mainRep->SetTexture(FirstImage, MainImage, imageTexure);
	auto imageTexure2 = TextureHandler->LookUpTexture(m_SegemntedImage);
	mainRep->SetImageSource(m_SegemntedImage, SecondImage, MainImage);
	mainRep->SetTexture(SecondImage, MainImage, imageTexure2);
}


void misSegmentationWithBrush::PulseHandler()
{
	SetMouseCursor();

	auto handleVal = GetReceivedMessage().wParam;
	auto message = GetReceivedMessage();
	if (message.message == WM_KEYDOWN)
	{
		switch (handleVal)
		{
		case  VK_END:

		{

			break;
		}
		case  VK_BACK:

		{

			brushObserver->Finalize();

			break;
		}

		case  VK_HOME:

		{
			SetMouseCursor();
		}

		}
	}
	m_Viewer->Render();

}

void misSegmentationWithBrush::SetMouseCursor()
{

	HCURSOR hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR2));
	SetCursor(hCursor);

}

