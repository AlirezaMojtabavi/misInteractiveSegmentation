 //misCompositeMapperTest
//

#pragma once


#include "vtkDICOMImageReader.h"
#include "vtkCubeSource.h"
#include "vtkBMPReader.h"
#include "vtkActor.h"
//=================================================================================
#include "misVisualizationUtils.h"
#include "misImageCallback.h"
#include "misInteractorSTyleImageExtend.h"
#include "vtkSphereSource.h"
#include "misVolumeSlicer.h"
#include "misAxialCompositeMapper.h"

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
#include "vtkTexturedSphereSource.h"

typedef itk::Point<float ,3>  PointType;

class misCompositeMapperTest
{
public:

	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misCompositeMapperTest Self;
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
	misCompositeMapperTest( )
	{

		slice=100;
		int *size;
		imageClalback=misImageCallback::New();

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misCompositeMapperTest::Render);
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
		//this->m_Viewer->AddAxis(axis);
		mis3dAxisLandmark::Pointer  pLnd=mis3dAxisLandmark::New();
		//pLnd->SetPosition(100,40,100);
		//m_Viewer->AddRepresentation(pLnd);
		//------------------------------------------------------------
		 
		//  textures definition 

		vtkTexture * texture1 =  vtkTexture::New();
		vtkTexture * texture2 =  vtkTexture::New();
		vtkTexture * texturecheckboard =  vtkTexture::New();

		vtkBMPReader * bmpReader = vtkBMPReader::New();
		//bmpReader->SetFileName("C:\\Users\\sRanjbar\\Downloads\\checkerboard.bmp");
		bmpReader->SetFileName("C:\\Users\\sRanjbar\\Documents\\Open GL\\checkboard mask - two loaded textures\\p.bmp");
		texturecheckboard->SetInputDataDataConnection(bmpReader->GetOutputPort());
		texturecheckboard->InterpolateOn();

	/*	vtkDICOMImageReader *dicomReader = vtkDICOMImageReader::New();
		
		dicomReader->SetDirectoryName("D:\\MIS data\\Patient1 - mohamad Mohamadi\\DICOM\\PA1\\ST1\\SE1\\");
		dicomReader->Update();
		texture1->SetInputDataDataConnection(dicomReader->GetOutputPort());
		texture1->InterpolateOn();

		dicomReader->SetDirectoryName("D:\\MIS data\\Patient1 - mohamad Mohamadi\\DICOM\\PA1\\ST1\\SE1\\");
		dicomReader->Update();
		texture2->SetInputDataDataConnection(dicomReader->GetOutputPort());
		texture2->InterpolateOn();
*/
		//------------------------------------------------------------

		misAxialCompositeMapper * textureMapper = misAxialCompositeMapper::New();
	/*	textureMapper->SetTexture(1,texture1);
		textureMapper->SetTexture(2,texture2);*/
		textureMapper->SetTexture(1,texturecheckboard);
		
		vtkTexturedSphereSource*  psp=vtkTexturedSphereSource::New();
		vtkPolyDataMapper*   pmapper=vtkPolyDataMapper::New();
		pmapper->SetInputDataData(psp->GetOutput());
		
		
		
		

		//-----------------------------------------------------------
	 
		// actor

		vtkActor * textureActor = vtkActor::New();
		textureActor->SetMapper(textureMapper);
		//textureActor->SetTexture(texturecheckboard);
		vtkRenderer*  pRendere = m_Viewer->GetRenderer();
		vtkActor*  pSpActor=vtkActor::New();
		pSpActor->SetMapper(pmapper);
		pRendere->AddActor(pSpActor);
		pRendere->AddActor(textureActor);
		
		
	}
	 
	//==========================================================================
	void Render()
	{
		this->m_Viewer->Render();


	}


	~misCompositeMapperTest(void)
	{
	}
};

