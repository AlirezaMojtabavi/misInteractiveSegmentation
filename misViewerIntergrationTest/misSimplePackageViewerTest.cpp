#include "StdAfx.h"

#include <memory>

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misIntegrationTestTools.h"
#include "misSimplePackageViewerTest.h"
#include "misWindow.h"
#include "misCoordinateSystemRepository.h"
#include "misDatasetManager.h"
#include "misTFIAddressMapper.h"
#include "misViewerFactory.h"

misSimplePackageViewerTest::misSimplePackageViewerTest( int &argc, char ** argv)
	: misIntegrationTestApplication(argc, argv)
{	
	std::shared_ptr<Iwindows> window = std::make_shared<misWindow>();
	window->set_m_Handle(GetMainWindow().Handle());
	window->GenerateRenderWindow(Iwindows::VolumeViewer);

	misSurgeryDirectionViewerType surgeryType;
	surgeryType.viewerType = Viewer3DLandmark;
	m_Viewer = std::make_shared<misPackage3DDataRenderingAdapter>(misDatasetManager::GetInstance()->GetCSCorrelationManager(), 
		window, 0, surgeryType,
		nullptr, nullptr, nullptr, nullptr);
	m_Viewer->GetViewer()->Get3DViewer()->SetWindow(window, 0);

	auto correlationManger = std::make_shared<misCoordinateSystemCorrelationTreeManager>();
	auto coordSysRepo = std::make_shared<misCoordinateSystemRepository>();
	misDatasetManager::GetInstance()->SetCSRepository(coordSysRepo);
	m_Viewer->SetWidgetType(SimpleCursor);
	InitVoreenShaders();
	LoadTFIMap();

	AddPackage(argv);
}

void misSimplePackageViewerTest::AddPackage(char ** argv)
{
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_Image->Update();
	misDatasetManager::GetInstance()->AddCoordinateSystem(m_Image);
	m_Package = std::make_shared<misSimpleDataPackage> (misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
	m_Package->SetImageToRelatedImageDataDependancy(m_Image);
	m_Viewer->SetVolumeViewingType(misVolumeViewingTypes::misAllViewing);
	auto appSetting = misApplicationSetting::GetInstance();
	m_Viewer->ShowPackage(
		m_Package,
		appSetting->m_VisulaizationSetting,
		appSetting->m_segmentationSetting,
		appSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel,
		true,
		SimpleCursor,
		std::map<misPlaneEnum,bool>());
}

 

void misSimplePackageViewerTest::InitVoreenShaders()
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
void misSimplePackageViewerTest::LoadTFIMap()
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
	misApplicationSetting::GetInstance()->SetTFIAddressMap(addressMapper);
	//SetColorList(GetTFILoader()->LoadTFI(addressMapper->GetTFIFileName(SPECT, misSkinviewing)));
}


void misSimplePackageViewerTest::PulseHandler()
{
	static double threshold = 0;
	if (GetReceivedMessage().wParam == VK_RIGHT)
	{
		threshold += 10;
		const double newThresholdForVolumerEndering = threshold + GetRenderingNormalizedThreshold(m_Image, ENT, misApplicationSetting::GetInstance()->m_VisulaizationSetting);
 		m_Image->SetSkinThreashold(newThresholdForVolumerEndering);
		auto volumeFactor = std::make_shared<VolumeFactory>();
		const auto volumeDep = volumeFactor->CreateTemporaryVolumeDependency(newThresholdForVolumerEndering, m_Image, ENT);
		VolumeDataDependencyListTypes volumes;
		volumes.push_back(volumeDep);
		m_Package->DeleteAllVolumedatas();
		m_Package->SetVolumeDataDependencies(volumes);
 		m_Viewer->UpdateColormap(m_Package->GetVolumeDataDependencies()[0]);
	}
	if (GetReceivedMessage().wParam == VK_LEFT)
	{
		threshold -= 10;
		const double newThresholdForVolumerEndering = threshold + GetRenderingNormalizedThreshold(m_Image, ENT, misApplicationSetting::GetInstance()->m_VisulaizationSetting);
		auto volumeFactor = std::make_shared<VolumeFactory>();
		const auto volumeDep = volumeFactor->CreateTemporaryVolumeDependency(newThresholdForVolumerEndering, m_Image, ENT);
		VolumeDataDependencyListTypes volumes;
		volumes.push_back(volumeDep);
		m_Package->DeleteAllVolumedatas();
		m_Package->SetVolumeDataDependencies(volumes);
		m_Viewer->UpdateColormap(m_Package->GetVolumeDataDependencies()[0]);
	}
	m_Viewer->GetViewer()->Render();

}