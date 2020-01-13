#include "StdAfx.h"

#include "PackageDentalVolumeRenderingIntgTest.h"
#include "mis2DToolActor.h"
#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misSurgeryDirectionViewerType.h"
#include "misTFIAddressMapper.h"
#include "misTFILoader.h"
#include "misVolumeRenderingColorMaps.h"
#include "misVoreenVolumeRenderingViewer.h"
#include "misWindow.h"
#include <misImageToTexturePropertyConvertor.h>
#include <misIntegrationTestTools.h>
#include <misTransFunctionBuilder.h>
#include <misVoreenRepresentation.h>
#include "misCoordinateSystemRepository.h"
#include "misDatasetManager.h"
#include "misViewerFactory.h"

PackageDentalVolumeRenderingIntgTest::PackageDentalVolumeRenderingIntgTest(int &argc, char ** argv)
	: misIntegrationTestApplication(argc, argv), m_Sphere(vtkSphereSource::New()), m_wnd(std::make_shared<misWindow>())
{
	auto viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	std::shared_ptr<Iwindows> window = std::make_shared<misWindow>();
	window->set_m_Handle(GetMainWindow().Handle());
	window->GenerateRenderWindow(Iwindows::VolumeViewer);
	std::shared_ptr<IVolumeRayCaster> volumeRenderer =
		std::make_shared<misVoreenVolumeRenderingViewer>(window->GetRenderer(0));
	misSurgeryDirectionViewerType surgeryType;
	surgeryType.viewerType = Viewer3DLandmark;
	m_Viewer = std::make_shared<misPackage3DDataRenderingAdapter>(misDatasetManager::GetInstance()->GetCSCorrelationManager(), 
		window, 0, surgeryType,
		nullptr, nullptr, nullptr, nullptr);
	window->GetRenderer(0)->SetBackground(.75, 0.75, 0.75);//(0,0,0)
	LoadTFIMap();
	auto correlationManger = std::make_shared<misCoordinateSystemCorrelationTreeManager>();
	auto coordSysRepo = std::make_shared<misCoordinateSystemRepository>();
	misDatasetManager::GetInstance()->SetCSRepository(coordSysRepo);
	m_Viewer->SetWidgetType(SimpleCursor);
	AddPackage();
	auto renderer = vtkOpenGLRenderer::New();
}

void PackageDentalVolumeRenderingIntgTest::AddPackage()
{
	misIntegrationTestTools testTools;
	auto image = testTools.LoadImageData("Images\\UpperJaw", 0);
	image->Update();
	misDatasetManager::GetInstance()->AddCoordinateSystem(image);
	auto package = std::make_shared<misSimpleDataPackage>
		(misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
	package->SetImageToRelatedImageDataDependancy(image);
	auto volumeFactor = std::make_shared<VolumeFactory>();
	auto volume = volumeFactor->CreateTemporaryVolumeDependency(image->GetCurrentTeethThreshold().get(), image, Dental);
	auto volumes = { volume };
	package->SetVolumeDataDependencies(volumes);
	m_Viewer->SetVolumeViewingType(misVolumeViewingTypes::misTeethViewing);
	auto appSetting = misApplicationSetting::GetInstance();
	m_Viewer->ShowPackage(package, appSetting->m_VisulaizationSetting, appSetting->m_segmentationSetting,
		appSetting->m_VisulaizationSetting.MinPlaneOpacityForSettingWindowLevel, true, SimpleCursor,
		std::map<misPlaneEnum, bool>());
}

void PackageDentalVolumeRenderingIntgTest::InitiVoreenShaders()
{
	glewInit();
	voreen = new voreen::VoreenApplication();
	voreen->init();
	voreen->initGL();
}

void PackageDentalVolumeRenderingIntgTest::PulseHandler()
{
	m_Viewer->GetViewer()->Render();
}

void PackageDentalVolumeRenderingIntgTest::LoadTFIMap()
{
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	addressMapper = std::make_shared<misTFIAddressMapper>();
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
			auto node = "misVisualizationSetting/TransFunctionsAddresses/" + modalityItr->second + "/" + viewingTypItr->second;
			if (appSettings->IsParamSet(node))
				addressMapper->SetTFIFileName(modalityItr->first, viewingTypItr->first, appSettings->GetString(node));
		}
	}
	misApplicationSetting::GetInstance()->SetTFIAddressMap(addressMapper);
}