#include "StdAfx.h"

#include "misSkinBoneCompositeTest.h"
#include <misVoreenRepresentation.h>
#include <misIntegrationTestTools.h>
#include <misImageToTexturePropertyConvertor.h>
#include <misTransFunctionBuilder.h>
#include "mis2DToolActor.h"
#include "misTFIAddressMapper.h"
#include "misBoneSkineVolume.h"
#include "misSurgeryDirectionViewerType.h"
#include "misPackage3DDataRenderingAdapter.h"
#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misCoordinateSystemRepository.h"
#include "misWindow.h"
#include "misDatasetManager.h"
#include "misViewerFactory.h"


misSkinBoneCompositeTest::misSkinBoneCompositeTest(int &argc, char ** argv)
	: misIntegrationTestApplication(argc, argv), m_Sphere(vtkSphereSource::New()), m_wnd(std::make_shared<misWindow>())
{

	std::shared_ptr<Iwindows> window = std::make_shared<misWindow>();
	window->set_m_Handle(GetMainWindow().Handle());
	window->GenerateRenderWindow(Iwindows::VolumeViewer);

	misSurgeryDirectionViewerType surgeryType;
	surgeryType.viewerType = Viewer3DLandmark;
	m_Viewer = std::make_shared<misPackage3DDataRenderingAdapter>(misDatasetManager::GetInstance()->GetCSCorrelationManager(), 
		window, 0,surgeryType,
		nullptr, nullptr, nullptr, nullptr);

	auto correlationManger = std::make_shared<misCoordinateSystemCorrelationTreeManager>();
	auto coordSysRepo = std::make_shared<misCoordinateSystemRepository>();
	misDatasetManager::GetInstance()->SetCSRepository(coordSysRepo);
	m_Viewer->SetWidgetType(SimpleCursor);
	InitiVoreenShaders();
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	AddPackage(argv[1], seriesNumber);
	

}



void misSkinBoneCompositeTest::AddPackage(std::string fileName, unsigned int serieIndex)
{
	misIntegrationTestTools testTools;
	auto image = testTools.LoadImageData(fileName, serieIndex);
	image->Update();
	misDatasetManager::GetInstance()->AddCoordinateSystem(image);
	std::shared_ptr<misSimpleDataPackage> package = 
		std::make_shared<misSimpleDataPackage>(misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
	misBoneSkineVolume skinVoluem;
	skinVoluem.SetImage(image);
	skinVoluem.SetMinThreshold(misSkin, -470);
	skinVoluem.SetMinThreshold(misBone, 170);
	auto volume = skinVoluem.GetVolumeData();
	package->SetImageToRelatedImageDataDependancy(image);
	package->AddNextVolumedata(volume);
	m_Viewer->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
	auto appSetting = misApplicationSetting::GetInstance();
	m_Viewer->ShowPackage(package, appSetting->m_VisulaizationSetting, appSetting->m_segmentationSetting,
		appSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel, true, SimpleCursor,
		std::map<misPlaneEnum, bool>());
}



void misSkinBoneCompositeTest::InitiVoreenShaders()
{
	glewInit();
	voreen = new voreen::VoreenApplication();
	voreen->init();
	voreen->initGL();

}



void misSkinBoneCompositeTest::PulseHandler()
{
	m_Viewer->GetViewer()->Render();

}

void misSkinBoneCompositeTest::LoadTFIMap()
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
	//misApplicationSetting::GetInstance()->SetTFIAddressMap(addressMapper);
	SetColorList(GetTFILoader()->LoadTFI(addressMapper->GetTFIFileName(SPECT, misVolumeViewingTypes::misSkinviewing)));
}

 
