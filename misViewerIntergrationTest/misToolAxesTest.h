//misToolAxesTest
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
#include "mis3dAxisLandmark.h"
#include "misSeedRepresentation.h"
#include "misFileReader.h"

typedef itk::Point<float ,3>  PointType;

class misToolAxesTest
{
public:

	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misToolAxesTest Self;
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
		if(!windowMain.Create(0, 0, 1000,800))
		{
			MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK);

		}



	}

	//==========================================================================
	misToolAxesTest( )
	{

		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misToolAxesTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		

		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());

		this->m_wnd->GenerateRenderWindow();
		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		this->m_Viewer=misHybridViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
		//-------------------------

		//-------------------------
		this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);

		this->m_PulseGenerator->RequestSetFrequency(20);
		this->m_PulseGenerator->RequestStart();
		misAxisProperty  axis;
		axis.m_GeoType=misAxisProperty::line;
		axis.z_Lenght=100;
		axis.y_Lenght=100;
		axis.x_Lenght=100;
		this->m_Viewer->AddAxis(axis);


		vtkPolyData* poly = misFileReader::ReadPolydataFromOBJFile("D:\\misSoloution\\misProject\\ROM FILES\\nav340.obj");	

		vtkPolyDataMapper *nav340Mapper = vtkPolyDataMapper::New();
		nav340Mapper->SetInputDataData(poly);

		vtkActor *nav340Actor = vtkActor::New();
		nav340Actor->SetMapper(nav340Mapper);

		poly = misFileReader::ReadPolydataFromOBJFile("D:\\misSoloution\\misProject\\ROM FILES\\NewRef.obj");
		vtkPolyDataMapper *newRefMapper = vtkPolyDataMapper::New();
		newRefMapper->SetInputDataData(poly);

		vtkActor *newRefActor = vtkActor::New();
		newRefActor->SetMapper(newRefMapper);

		this->m_Viewer->GetRenderer()->AddActor(nav340Actor);
		this->m_Viewer->GetRenderer()->AddActor(newRefActor);
	 

	}
 
 
	//==========================================================================
	void Render()
	{
		this->m_Viewer->Render();


	}


	~misToolAxesTest(void)
	{
	}
};

