#include "StdAfx.h"

#include "misSurfaceGenerationTest.h"
#include "misIntegrationTestTools.h"
#include "misExtractExternalSurface.h"
#include "misSurfaceRepresentation.h"
#include "misApplicationSetting.h"
#include "misVoreenRepresentation.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misTransFunctionBuilder.h"
#include "MedicalCameraDirection.h"


misSurfaceGenerationTest::misSurfaceGenerationTest(int &argc, char ** argv)
	:misIntegrationTestApplication(argc, argv), m_wnd(std::make_shared<misWindow>())
{
	m_arg = argv;
	m_wnd->set_m_Handle(GetMainWindow().Handle());
	m_wnd->GenerateRenderWindow(Iwindows::NoViewer);
	auto viewer = std::make_shared<mis3DViewer>(vtkPointPicker::New());
	auto medicalDirection = std::make_shared<parcast::MedicalCameraDirection>(viewer);
	m_Viewer = std::make_shared<mis3DVolumeRenderer>(nullptr, m_wnd, 0, viewer, nullptr, nullptr, nullptr, medicalDirection,
	                                                 nullptr);
	m_wnd->GetRenderer(0)->SetBackground(0.2,1,1);
	InitVolumeRendering();
	AddVolume();
	misROI roiBox(0, 300, 0, 300, 0, 300);
	m_Viewer->SetROI(roiBox);
	m_Viewer->ROIWidgetActivation(true);
	m_arg = argv;
}


void misSurfaceGenerationTest::InitVolumeRendering()
{
	voreen::VoreenApplication* m_Voreen=new voreen::VoreenApplication();
	m_Voreen->init();
	m_Voreen->initGL();
	glewInit();
}

void misSurfaceGenerationTest::AddSpineIsoSurface(char ** argv)
{
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_Image->Update();

	double * roi = m_Viewer->GetROICompressData();
	vtkExtractVOI* pImageReslicer = vtkExtractVOI::New();
	double* spacing = m_Image->GetSpacing();

	int extend[6];
	extend[0] = roi[0]/spacing[0];
	extend[1] = roi[1]/spacing[0];
	extend[2] = roi[2]/spacing[1];
	extend[3] = roi[3]/spacing[1];
	extend[4] = roi[4]/spacing[2];
	extend[5] = roi[5]/spacing[2];
	pImageReslicer->SetVOI(extend[0],extend[1],extend[2],extend[3],extend[4],extend[5]);
	pImageReslicer->SetSampleRate(1,1,1);
	pImageReslicer->SetInputData(m_Image->GetRawImageData());
	pImageReslicer->Update();

	misExtractExternalSurface externalSurfaceExtractor;
	vtkPolyData* pResPoly = externalSurfaceExtractor.ExtractOuterSurface(pImageReslicer->GetOutput(),
		misApplicationSetting::GetInstance()->m_VisulaizationSetting.BoneThresholdForCT);
	
	auto surface = std::make_shared<misSurfaceRepresentation>("");
	//surface->SetPolyData(pResPoly);
	surface->SetPosition(300, 0, 0);
	m_Viewer->AddRepresentation(surface);
	vtkPolyDataWriter* polyWriter = vtkPolyDataWriter::New();
	polyWriter->SetInputData(pResPoly);
	polyWriter->SetFileName("Spine.vtk");

	polyWriter->Write();

	

}

void misSurfaceGenerationTest::AddHeadIsoSurface(char ** argv)
{
	int seriesNumber;
	std::istringstream seriesNumberStream(argv[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(argv[1], seriesNumber);
	m_Image->Update();
 
	

	//misExtractExternalSurface externalSurfaceExtractor;
	//vtkPolyData* pResPoly = externalSurfaceExtractor.ExtractOuterSurface(pImageReslicer->GetOutput(),
	//	misApplicationSetting::GetInstance()->m_VisulaizationSetting.BoneThresholdForCT);

	auto segmentedSurface = vtkSmartPointer<vtkContourFilter>::New();
	segmentedSurface->ComputeGradientsOff();
	segmentedSurface->ComputeNormalsOff();
	segmentedSurface->SetInputData(m_Image->GetRawImageData());
	segmentedSurface->SetNumberOfContours(1);
	segmentedSurface->SetValue(0, -470);
	segmentedSurface->Update();

	auto surface = std::make_shared<misSurfaceRepresentation>("");
	auto prpo = vtkProperty::New();
	prpo->SetColor(1, 0, 0);
	surface->AddPolyData(segmentedSurface->GetOutput(), prpo);
	surface->SetPosition(300, 0, 0);
	m_Viewer->AddRepresentation(surface);
	vtkPolyDataWriter* polyWriter = vtkPolyDataWriter::New();
	polyWriter->SetInputData(segmentedSurface->GetOutput());
	polyWriter->SetFileName("head.vtk");

	polyWriter->Write();

	

}

void misSurfaceGenerationTest::AddVolume()
{
	int seriesNumber;
	std::istringstream seriesNumberStream(m_arg[2]);
	seriesNumberStream >> seriesNumber;
	misIntegrationTestTools testTools;
	m_Image = testTools.LoadImageData(m_arg[1], seriesNumber);
	m_Image->Update();

	auto voreenRep = std::shared_ptr<misVoreenRepresentation>();
	m_Viewer->SetMainRepresentation(voreenRep, UNKnownDirection);
	m_Viewer->InitializeCornerProperties();
	misImageToTexturePropertyConvertor convertor1;
	misTexturePropertyStruct texProp1 = convertor1(m_Image);
	misOpenglTexture* pTexture= new misOpenglTexture(texProp1, tgt::Texture::LINEAR);
	misTransFunctionBuilder  tfbuilder;	
	auto tr= tfbuilder.GenerateTransferFunction(texProp1.GetTableRange(), MRI);
	m_Viewer->SetVolume(pTexture,tr);
}
 
void misSurfaceGenerationTest::PulseHandler()
{
	if (GetReceivedMessage().wParam == VK_BACK)
	{
			AddSpineIsoSurface(m_arg);
	}
	if (GetReceivedMessage().wParam == VK_SPACE)
	{
			AddHeadIsoSurface(m_arg);
	}

	m_Viewer->Render();

}
