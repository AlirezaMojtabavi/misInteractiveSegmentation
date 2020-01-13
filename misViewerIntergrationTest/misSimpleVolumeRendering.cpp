#include "StdAfx.h"

#include "misSimpleVolumeRendering.h"
#include <misVoreenRepresentation.h>
#include <misIntegrationTestTools.h>
#include <misImageToTexturePropertyConvertor.h>
#include <misTransFunctionBuilder.h>
#include "mis2DToolActor.h"
#include "misTFIAddressMapper.h"
#include "misVoreenVolumeRenderingViewer.h"
#include "misWindow.h"
#include "misVolumePointPicker.h"
#include "misUpdateLandmarkCameraView.h"
#include "MedicalCameraDirection.h"


misSimpleVolumeRendering::misSimpleVolumeRendering(int &argc, char ** argv)
	: misIntegrationTestApplication(argc, argv), m_Sphere(vtkSphereSource::New()), m_wnd(std::make_shared<misWindow>())
{
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::VolumeViewer);
	InitiVoreenShaders();
	auto viewer = std::make_shared<mis3DViewer>(misVolumePointPicker::New());
	std::shared_ptr<IVolumeRayCaster> volumeRenderer =
		std::make_shared<misVoreenVolumeRenderingViewer>(m_wnd->GetRenderer(0));
	auto corner = std::make_shared<misCornerProperties>(misApplicationSetting::GetInstance()->m_WorkflowButtonSet);
	m_Viewer = std::make_shared<mis3DVolumeRenderer>(nullptr, m_wnd, 0, viewer, corner,
		std::make_shared<misUpdateLandmarkCameraView>(viewer, 30),
		nullptr, nullptr, volumeRenderer);


	m_wnd->GetRenderer(0)->SetBackground(.75, 0.75, 0.75);//(0,0,0)
	refernceCheck = m_wnd->GetRenderer(0);
	//AddSphere();
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_Image->Update();
	AddVolume();

}





void misSimpleVolumeRendering::AddVolume()
{
	auto  voreenRep = std::make_shared<misVoreenRepresentation>();
	m_Viewer->SetMainRepresentation(voreenRep, UNKnownDirection);
	m_Viewer->InitializeCornerProperties();
	misImageToTexturePropertyConvertor convertor1;
	misTexturePropertyStruct texProp1 = convertor1(m_Image);
	misOpenglTexture* pTexture = new misOpenglTexture(texProp1, tgt::Texture::LINEAR);
	//misTransFunctionBuilder  tfbuilder;	
	auto tr = GenerateTransferFunction(texProp1.GetTableRange(), CT);
	m_Viewer->SetVolume(pTexture, tr);
}

void misSimpleVolumeRendering::InitiVoreenShaders()
{
	glewInit();
	voreen = new voreen::VoreenApplication();
	voreen->init();
	voreen->initGL();

}



void misSimpleVolumeRendering::PulseHandler()
{
	m_Viewer->Render();
	if (GetReceivedMessage().wParam == VK_END)
		ReInitialize();

}

void misSimpleVolumeRendering::LoadTFIMap()
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

std::shared_ptr<TransFuncIntensity> misSimpleVolumeRendering::GenerateTransferFunction(double* TableRange, misImageDataModality modality)
{

	auto IntensityFunc = std::make_shared<TransFuncIntensity>();


	if (modality == SPECT)
	{

		TransFuncMappingKey *key0 = new TransFuncMappingKey(0.0, tgt::vec4(0, 0, 0, 0));
		IntensityFunc->addKey(key0);

		float key1Value = ConvertIntensityToKeyValue(TableRange, 20);
		TransFuncMappingKey *key1 = new TransFuncMappingKey(key1Value, tgt::vec4(0, 0, 0, 0));
		IntensityFunc->addKey(key1);

		float key2Value = ConvertIntensityToKeyValue(TableRange, 28);
		TransFuncMappingKey *key2 = new TransFuncMappingKey(key2Value, tgt::vec4(82, 198, 247, 2));
		IntensityFunc->addKey(key2);

		float key3Value = ConvertIntensityToKeyValue(TableRange, 30);
		TransFuncMappingKey *key3 = new TransFuncMappingKey(key3Value, tgt::vec4(82, 198, 247, 2));
		IntensityFunc->addKey(key3);

		float key4Value = ConvertIntensityToKeyValue(TableRange, 35);
		TransFuncMappingKey *key4 = new TransFuncMappingKey(key4Value, tgt::vec4(82, 198, 247, 2));
		IntensityFunc->addKey(key4);

		float key5Value = ConvertIntensityToKeyValue(TableRange, 40);
		TransFuncMappingKey *key5 = new TransFuncMappingKey(key5Value, tgt::vec4(82, 198, 247, 0));
		IntensityFunc->addKey(key5);

		float key6Value = ConvertIntensityToKeyValue(TableRange, 42);
		TransFuncMappingKey *key6 = new TransFuncMappingKey(key6Value, tgt::vec4(220, 247, 43, 10));
		IntensityFunc->addKey(key6);

		float key7Value = ConvertIntensityToKeyValue(TableRange, 80);
		TransFuncMappingKey *key7 = new TransFuncMappingKey(key7Value, tgt::vec4(220, 247, 43, 10));
		IntensityFunc->addKey(key7);

		float key8Value = ConvertIntensityToKeyValue(TableRange, 85);
		TransFuncMappingKey *key8 = new TransFuncMappingKey(key8Value, tgt::vec4(220, 247, 43, 0));
		IntensityFunc->addKey(key8);

		float key99Value = ConvertIntensityToKeyValue(TableRange, 86);
		TransFuncMappingKey *key99 = new TransFuncMappingKey(key99Value, tgt::vec4(255, 0, 0, 0));
		IntensityFunc->addKey(key99);

		float key9Value = ConvertIntensityToKeyValue(TableRange, 87);
		TransFuncMappingKey *key9 = new TransFuncMappingKey(key9Value, tgt::vec4(255, 0, 0, 3));
		IntensityFunc->addKey(key9);

		float key10Value = ConvertIntensityToKeyValue(TableRange, 120);
		TransFuncMappingKey *key10 = new TransFuncMappingKey(key10Value, tgt::vec4(255, 0, 0, 3));
		IntensityFunc->addKey(key10);
		//
		float key11Value = ConvertIntensityToKeyValue(TableRange, 160);
		TransFuncMappingKey *key11 = new TransFuncMappingKey(key11Value, tgt::vec4(255, 0, 0, 0));
		IntensityFunc->addKey(key11);
	}
	if (modality == CT)
	{
		// threshold = -450 for vtkImageData
		// threshold = 2000 for dcmtkImage
		float skinthresholdvalue = ConvertIntensityToKeyValue(TableRange, -450.0f);
		float bonethresholdvalue = ConvertIntensityToKeyValue(TableRange, 500.0f);
		TransFuncMappingKey *key0 = new TransFuncMappingKey(0.0f, tgt::vec4(0, 0, 0, 0));
		IntensityFunc->addKey(key0);
		TransFuncMappingKey *skin0 = new TransFuncMappingKey(skinthresholdvalue, tgt::col4(247, 222, 166, 0));
		IntensityFunc->addKey(skin0);
		TransFuncMappingKey *skin1 = new TransFuncMappingKey(skinthresholdvalue + 0.03f, tgt::col4(247, 222, 166, 50));
		IntensityFunc->addKey(skin1);
		TransFuncMappingKey *key1 = new TransFuncMappingKey(1.0f, tgt::col4(255, 255, 255, 255));
		IntensityFunc->addKey(key1);
	}

	if (modality == MRI)
	{

		float skinthresholdvalue = ConvertIntensityToKeyValue(TableRange, 100.0);;
		TransFuncMappingKey *key0 = new TransFuncMappingKey(0.0f, tgt::vec4(0, 0, 0, 0));
		IntensityFunc->addKey(key0);
		TransFuncMappingKey *skin0 = new TransFuncMappingKey(skinthresholdvalue, tgt::col4(247, 222, 166, 0));
		IntensityFunc->addKey(skin0);
		TransFuncMappingKey *skin1 = new TransFuncMappingKey(skinthresholdvalue + 0.05f, tgt::col4(247, 0, 166, 50));
		IntensityFunc->addKey(skin1);
		TransFuncMappingKey *key1 = new TransFuncMappingKey(1.0f, tgt::col4(255, 255, 255, 255));
		IntensityFunc->addKey(key1);
	}
	return IntensityFunc;

}
float misSimpleVolumeRendering::ConvertIntensityToKeyValue(const double* TableRange, double val)
{
	if (TableRange)
	{
		float key = static_cast<float> ((val - TableRange[0]) / (TableRange[1] - TableRange[0]));
		return key;
	}
	return -1.0;
}

void misSimpleVolumeRendering::ReInitialize()
{
	m_wnd = std::make_shared<misWindow>();
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::VolumeViewer);
	InitiVoreenShaders();
	auto viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	std::shared_ptr<IVolumeRayCaster> volumeRenderer =
		std::make_shared<misVoreenVolumeRenderingViewer>(m_wnd->GetRenderer(0));
	auto medicalDirection = std::make_shared<parcast::MedicalCameraDirection>(viewer);
	m_Viewer = std::make_shared<mis3DVolumeRenderer>(nullptr, m_wnd, 0, viewer, nullptr, nullptr, nullptr, medicalDirection, volumeRenderer);
	m_wnd->GetRenderer(0)->SetBackground(1, 0, 0);//(0,0,0)
	m_Viewer->Render();
	AddVolume();
}

