//misLandmarkTest
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
#include "misGpuVolumeRepresentation.h"
#include "misDIRReader.h"
#include "vtkTimerLog.h"
#include "mis3dAxisLandmark.h"
#include "misSeedRepresentation.h"

typedef itk::Point<float ,3>  PointType;

class misLandmarkTest
{
public:

	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misLandmarkTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
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
	misLandmarkTest( )
	{

		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misLandmarkTest::Render);
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
  
		double  position1[3];
		
AddCorrectionLabel(position1);
position1[0]=100;
		position1[1]=300;
		position1[2]=100;
		AddCorrectionLabel(position1);

	}
misSeedRepresentation::Pointer  m_RegisterdPointSeedRep;
	
void AddCorrectionLabel(double pos[3])
	{


		if(!m_RegisterdPointSeedRep )
		{
			m_RegisterdPointSeedRep = misSeedRepresentation::New("3d model land mark");
			m_RegisterdPointSeedRep->SetCategory(RegistrationErrorCorresponded);
			m_RegisterdPointSeedRep->Validate();
		}


		double direction[3];
		double* posEye;
		double* up;
		m_RegisterdPointSeedRep->SetPosition(pos);


		m_RegisterdPointSeedRep->UpdateAsUnderCapture();
		misItkPointTypecamp=m_RegisterdPointSeedRep->GetViewEyePosition();
		double  lndLabelPosition[3];
		lndLabelPosition[0]=camp[0];
		lndLabelPosition[1]=camp[1];
		lndLabelPosition[2]=camp[2];
		m_RegisterdPointSeedRep->SetLabelPosition(lndLabelPosition);


		m_Viewer->AddRepresentation(m_RegisterdPointSeedRep);

		m_RegisterdPointSeedRep->SetVisibilityOn();

	}

	//==========================================================================
	void Render()
	{
		this->m_Viewer->Render();


	}


	~misLandmarkTest(void)
	{
	}
};

