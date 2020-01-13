//

#pragma once

 
#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"

#include "vtkImageMapToWindowLevelColors.h"

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
#include "misGpuVolumeRepresentation.h"
#include "misDIRReader.h"
#include "vtkTimerLog.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misFpsVolumeTest
{
public:
 
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misFpsVolumeTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   

	misHybridViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	void LoadGui()
	{	
		//a window object

		HINSTANCE  hInstance=GetModuleHandle(0);
		if(!windowMain.Create(0, 0, 400,400))
		{
			MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK);

		}

		 

	}

	//==========================================================================
	misFpsVolumeTest( )
	{
	 
		slice=100;
		int *size;
		imageClalback=misImageCallback::New();
		CameraRadius=500;
		alpha=0;
		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misFpsVolumeTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		
		m_wnd->FPSDisplayOFF();
		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		this->m_Viewer=misHybridViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
 		//-------------------------
		 
		//-------------------------
		this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);
	 
		this->m_PulseGenerator->RequestSetFrequency(100);
		this->m_PulseGenerator->RequestStart();
		this->AddImage();

		misGpuVolumeRepresentation::Pointer pSurface=misGpuVolumeRepresentation::New("lndSelection");
		pSurface->SetImage(m_pImage);
		pSurface->m_VolumeData->SetMinThreshold(misAllViewing,500);
		pSurface->m_VolumeData->SetViewableObject(misAllViewing,1);
		pSurface->UpdatePiecWiseFunction();

		vtkTimerLog*  pLoggerTime=vtkTimerLog::New();
		m_Viewer->Render();
		m_Viewer->GetRenderer()->ResetCamera();

	 
	 m_Viewer->AddRepresentation(pSurface);
	 
pLoggerTime->StartTimer();
	 

pLoggerTime->StopTimer();
double   elabsed=pLoggerTime->GetElapsedTime();
cout<<"time in ms  :"<<(elabsed*1000)/100.0;

	}
		misGpuAxialMultiplaneRepresentation::Pointer  plane;
	misImage*  m_pImage;
	float CameraRadius;
	float alpha;
	void AddImage()
	{
		 

		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
 
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("D:\\Dicom Data\\Davood Kaveh\\Main CT\\DICOM\\PA1\\ST1\\SE1\\");

		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage=  m_pDicomReader->Get3DImageData(adrees); */

	 
	}

	//==========================================================================
	void Render()
	{
		alpha=alpha+1;
		if(alpha>360)
			alpha=0;
		float rdd=vtkMath::RadiansFromDegrees(alpha);
		float  x=CameraRadius*sin(rdd);
		float  z=CameraRadius*cos(rdd);
		m_Viewer->GetRenderer()->GetActiveCamera()->SetPosition(x,z,500);
 


		this->m_Viewer->Render();
		 

	}


	~misFpsVolumeTest(void)
	{
	}
};

