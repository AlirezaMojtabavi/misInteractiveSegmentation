#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"

#include "misAxialRepresentation.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "misCoronalRepresentation.h"
#include "vtkPNGReader.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTexturedActor2D.h"
#include "vtkProperty2D.h"
#include "misGpuAxialMultiplaneRepresentation.h"
#include "misGpuCoronalMultiplaneRepresentation.h"
#include "vtkLight.h"
#include "misGpuSagittalMultiplaneRepresentation.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h"
#include "vtkImageCast.h"
#include "misOpenGLGPUVolumeRayCastMapper.h"
#include "vtkColorTransferFunction.h"
#include "vtkPiecewiseFunction.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "misHybridViewer.h"
#include "..\..\..\missolution-phase 4\missoloution\misvisualization\misgpuvolumerenderingrepresentation.h"

class misVolumeRenderingTest
{
public:
	
	int m_Type;
	float  slice;
	double  pos[3];

	typedef misVolumeRenderingTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   

	misHybridViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;
	

	int * m_Size;

	void LoadGui()
	{	
		//a window object

		HINSTANCE  hInstance=GetModuleHandle(0);
		if(!windowMain.Create(0, 0, 1000,800))
		{
			MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK);

		}



	}

	misVolumeRenderingTest(int type)
	{
		m_Type=type;
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misVolumeRenderingTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		

		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		this->m_Viewer=misHybridViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
		//		m_Viewer->SetCamerSettingInternaly(true);
		//-------------------------
		vtkRenderer *rendere=this->m_Viewer->GetRenderer();
		//LoadExtensions(rendere->GetRenderWindow());
		//rendere->LightFollowCameraOn();
		//rendere->RemoveAllLights();
		rendere->TwoSidedLightingOn();
		//		rendere->UpdateLightGeometry();
		vtkLight* pLight=vtkLight::New();
		pLight->SetDiffuseColor(0.8,0.8,0.8);
		pLight->SetAmbientColor(0.8,0.8,0.8);

		pLight->SetLightTypeToHeadlight();
		rendere->AddLight(pLight);
		//pLight->SetPosition()
		size=rendere->GetRenderWindow()->GetSize();

		double  sized[2];
		sized[0]=size[0];
		sized[1]=size[1];


		//	InitLogger();
		imageClalback->SetSize(sized);
		//-------------------------
		this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);

		this->m_PulseGenerator->RequestSetFrequency(20);
		this->m_PulseGenerator->RequestStart();
		this->AddImage();





	}
	

	void AddImage()
	{

		vtkDICOMImageReader* pImageReader=vtkDICOMImageReader::New();
		pImageReader->SetDirectoryName("E:\\Dicom Data\\Face man  Phantom\\DICOM\\PA1\\ST1\\SE4");
		pImageReader->Update();

		misOpenGLGPUVolumeRayCastMapper *mapper2 = misOpenGLGPUVolumeRayCastMapper::New();
		mapper2->SetInputDataData(pImageReader->GetOutput());

		vtkVolume *volume2 = vtkVolume::New();

		vtkColorTransferFunction *ColorFunction2=vtkColorTransferFunction::New();
		vtkPiecewiseFunction *opacityFun2=vtkPiecewiseFunction::New();
		ColorFunction2->ClampingOff();
		opacityFun2->ClampingOff();

		vtkVolumeProperty *property2=vtkVolumeProperty::New();
		property2->SetColor(ColorFunction2);
		property2->SetDiffuse(0.3);
		property2->SetAmbient(0.1);

		int num2=property2->GetColorChannels();

		property2->SetScalarOpacity(opacityFun2);
		property2->SetInterpolationTypeToLinear();

		ColorFunction2->AddRGBSegment(-1024, 0.0, 0.0, 0.0, 
			-200, 0.0, 0.0, 0.0);
		ColorFunction2->AddRGBSegment(-200, 0.0, 0.0, 0.0, 
			0, 0.0, 0.0, 0.0);
		ColorFunction2->AddRGBSegment(0, 1.0, 0.0, 0.0, 
			4000, 1.0, 0.0, 0.0);

		opacityFun2->AddSegment(-1024, 0.0, -200, 0.0); 
		opacityFun2->AddSegment(-200, 0.0, 0, 0.0); 
		opacityFun2->AddSegment(0.0, 1.0, 3000, 1.0); 

		mapper2->SetBlendModeToComposite();

		property2->ShadeOn();
		volume2->SetProperty(property2);
		volume2->SetMapper(mapper2);

		vtkRenderer *renderer = this->m_Viewer->GetRenderer();
		renderer->AddViewProp(volume2);

		renderer->GetActiveCamera()->SetPosition(0,0,5);
		renderer->GetActiveCamera()->SetFocalPoint(0,0,0);
		renderer->GetActiveCamera()->SetViewUp(0,1,0);


	}

	//==========================================================================
	void Render()
	{
		this->m_Viewer->Render();


	}


	~misVolumeRenderingTest(void)
	{
	}
};

