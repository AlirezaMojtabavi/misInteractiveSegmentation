 #include "stdafx.h"
#include "SegmentationWithBrush4View.h"

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misGroupViewerSettingFinder.h"
#include "misIntegrationTestTools.h"
#include "misToolShapeBuilder.h"
#include "misTFIAddressMapper.h"
//#include "misSolutionControl.h"
#include "misCoordinateSystemRepository.h"
#include "misDataSetManager.h"
//#include "misTabAndSubTabActicationControl.h"
#include "misGroupViewerFactory.h"
#include "misTabAndSubTabName.h"
#include "misViewerFactory.h" 
#include "IToolRepresentation.h"
#include "misENTBraineNavigationLayoutFactory.h"
#include "BrushImageGeneration.h"
#include "misCursorService.h"
#include "BackToPanMode.h"
#include <vtkPointPicker.h>
#include "misBrushViewerFactory.h"
#include "resource.h"
#include <misMathUtils.h>
#include "misImageToTextureMap.h"

 using namespace std;

SegmentationWithBrush4View::SegmentationWithBrush4View(int &argc, char ** argv)
	:misIntegrationNView(argc, argv)
{
	vtkObject::GlobalWarningDisplayOff();
	
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_SegemntedImage = testTools.LoadImageData(argv[1], seriesNumber);
	m_SegemntedImage->Update();
	auto segementationIMage = m_SegemntedImage->GetRawImageData();
	int* dims = m_Image->GetDimensions();
	misPixelType* pointerImage = (misPixelType*)segementationIMage->GetScalarPointer();
	for (int z = 0; z < dims[2]; z++)
		for (int y = 0; y < dims[1]; y++)
			for (int x = 0; x < dims[0]; x++)
				pointerImage[z*(dims[1] * dims[0]) + y * dims[0] + x] = -1000;

	m_Image->SetConfirmedDirection(true);
	m_SegemntedImage->SetConfirmedDirection(true);

	std::shared_ptr<misCoordinateSystemRepository> reposity = make_shared<misCoordinateSystemRepository>();
	misDatasetManager::GetInstance()->SetCSRepository(reposity);
	correlationManager = make_shared<misCoordinateSystemCorrelationTreeManager>();

	misDatasetManager::GetInstance()->AddCoordinateSystem(m_Image);
	misGroupViewerSettingFinder groupViewerSettingFinder;
	auto layout = groupViewerSettingFinder.MakePckageGroupViewer("NavigationTab");
	misGroupViewerFactory groupViewerFactory;
	auto subtabModel = GetSubTabModel();
	subtabModel->SetName(misTabAndSubTabName::GetInstanse()->GetSubTabNameNavigatoinMain(ENT));
	m_GroupViewer = groupViewerFactory.Create(layout, subtabModel, ENT,
		std::make_shared<misBrushViewerFactory>(), correlationManager, 5);

	auto slicers = m_GroupViewer->Get2DViewers();
	brushObserverList.clear();
	for (auto i = 0; i < slicers.size(); i++)
	{
		auto brushobserver = vtkSmartPointer<BrushImageGeneration>::New();
		brushobserver->Create(slicers[i]->Get3DViewer(), slicers[i], slicers[i]->GetCornerProperties(), slicers[i]->GetDummySubject(), slicers[i]->GetCursorService(),
			slicers[i]->GetCameraService());
		brushObserverList.push_back(brushobserver);

		const auto pairEvent3 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::MouseMoveEvent, brushObserverList[i]);
		auto pairEvent4 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::LeftButtonPressEvent, brushObserverList[i]);
		auto pairEvent5 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
			vtkCommand::LeftButtonReleaseEvent, brushObserverList[i]);
		slicers[i]->AddPointSelectObserver(pairEvent3);
		slicers[i]->AddPointSelectObserver(pairEvent4);
		slicers[i]->AddPointSelectObserver(pairEvent5);
	}
	misIntegrationTestTools::InitializeRendering(m_GroupViewer->GetAllViewers());
	packages = misDatasetManager::GetInstance()->GetPackageDataS();
	InitiVoreenShaders();
	LoadTFIMap();

	auto tansform = vtkTransform::New();
	tansform->Identity();
	auto identityMat = misMathUtils::CreateTransform(tansform->GetMatrix());

	//correlationManager->SetTransform(image->GetUID(), SegemntedImage->GetUID(), identityMat);
	packages[0]->SetImageToRelatedImageDataDependancy(m_SegemntedImage);

	auto volumeSlicers = m_GroupViewer->Get2DViewers();
	auto allSlicer = m_GroupViewer->GetAllViewers();
	std::shared_ptr<I3DViewer> viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	auto interactorStyleImageExtend = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	
	auto measureMent = misMeasurment::New();
	auto imageStyle = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	auto dummy = misVolumeRendererContainer::New();
	auto cursorService = std::make_shared<misCursorService>();
	auto backToPan = std::make_shared<BackToPanMode>(measureMent, imageStyle, viewer, dummy);
	auto pan = std::make_shared<BackToPanMode>(measureMent, interactorStyleImageExtend, viewer, dummy);
	auto corner = std::make_shared<misCornerProperties>(misApplicationSetting::GetInstance()->m_WorkflowButtonSet);
	m_GroupViewer->ShowPackage(packages[0], 0);

	//brushObserver->CreateTExture();
}
void SegmentationWithBrush4View::InitiVoreenShaders()
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

 

void SegmentationWithBrush4View::PulseHandler()
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

		
		case VK_BACK:
		{

			brushObserverList[0]->Finalize();
			m_GroupViewer->Reset();
			auto package = std::make_shared<misSimpleDataPackage>(misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
			package->SetImageToRelatedImageDataDependancy(m_SegemntedImage);
			package->SetImageToRelatedImageDataDependancy(m_Image);
			m_GroupViewer->ShowPackage(package, false);
			m_GroupViewer->SetColorValueToTexture(FirstImage, misDoubleColorStruct(1,0,0, .5));
		}
		
		case  'a':
		case  'A':

		{
			for (auto observer : brushObserverList)
				observer->Activate();
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->SetInteractionState(InteractionState::WidgetInteractionState);
				viewer->SetInteractionMode(NoState);
 			}
			break;
		}

		case  'd':
		case  'D':

		{
			for (auto observer : brushObserverList)
				observer->DeActive();
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->SetInteractionState(InteractionState::ContrastState);
				viewer->SetInteractionMode(ContrastEvent);
			}

			break;
		}
		case 'r':
		case 'R':

		{
			for (auto viewer : m_GroupViewer->Get2DViewers())
			{
				viewer->ResetContrast();
 			}
			break;
		}
		}
	}
	m_GroupViewer->Render();


}
void SegmentationWithBrush4View::UpdateTexture()
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexure = TextureHandler->LookUpTexture(m_Image);
	auto slicers = m_GroupViewer->Get2DViewers();
	for (auto slicer : slicers)
	{
		auto mainRep = slicer->GetImageRprensentaion();
		mainRep->SetImageSource(m_Image, FirstImage, MainImage);
		mainRep->SetTexture(FirstImage, MainImage, imageTexure);

		
		auto imageTexure2 = TextureHandler->LookUpTexture(m_SegemntedImage);
		mainRep->SetImageSource(m_SegemntedImage, SecondImage, MainImage);
		mainRep->SetTexture(SecondImage, MainImage, imageTexure2);

	}
}
void SegmentationWithBrush4View::LoadTFIMap()
{
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	auto addressMapper = std::make_shared<misTFIAddressMapper>();
	std::map<misImageDataModality, std::string> modalityStrings;
	std::map<misVolumeViewingTypes, std::string> viewingTypeStrings;
	modalityStrings[CT] = "CT";
	modalityStrings[MRI] = "MRI";
	modalityStrings[fMRI] = "fMRI";
	modalityStrings[XRay] = "XRay";
	modalityStrings[DXRay] = "DXRay";
	modalityStrings[PET] = "PET";
	modalityStrings[SPECT] = "SPECT";
	modalityStrings[Angio] = "Angio";
	modalityStrings[DAngio] = "DAngio";
	modalityStrings[US] = "US";
	modalityStrings[NM] = "NM";
	modalityStrings[NoData] = "NoData";
	viewingTypeStrings[misVolumeViewingTypes::misSkinFilledViewing] = "SkinFilledViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSkinviewing] = "SkinViewing";
	viewingTypeStrings[misVolumeViewingTypes::misBoneViwing] = "BoneViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSpineViewing] = "SpineViewing";
	viewingTypeStrings[misVolumeViewingTypes::misMetalViewing] = "MetalViewing";
	viewingTypeStrings[misVolumeViewingTypes::misAllViewing] = "AllViewing";
	viewingTypeStrings[misVolumeViewingTypes::misSinusesViewing] = "SinusesViewing";
	viewingTypeStrings[misVolumeViewingTypes::misTeethViewing] = "TeethViewing";
	viewingTypeStrings[misVolumeViewingTypes::UnsetViewingType] = "UnsetViewingType";
	viewingTypeStrings[misVolumeViewingTypes::misAnimalViewing] = "AnimalViewing";
	for (auto modalityItr = modalityStrings.cbegin(); modalityItr != modalityStrings.cend(); ++modalityItr)
	{
		for (auto viewingTypItr = viewingTypeStrings.cbegin(); viewingTypItr != viewingTypeStrings.cend(); ++viewingTypItr)
		{
			std::string node =
				"misVisualizationSetting/TransFunctionsAddresses/" + modalityItr->second + "/" + viewingTypItr->second;
			if (appSettings->IsParamSet(node))
				addressMapper->SetTFIFileName(modalityItr->first, viewingTypItr->first, appSettings->GetString(node));
		}
	}
	misApplicationSetting::GetInstance()->SetTFIAddressMap(addressMapper);
}
void SegmentationWithBrush4View::SetMouseCursor()
{

	HCURSOR hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR2));
	SetCursor(hCursor);

}
