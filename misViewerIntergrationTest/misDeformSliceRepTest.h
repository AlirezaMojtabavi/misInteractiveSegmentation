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
//#include "misGpuAxialPlaneRep3dc.h"
//#include "misGpuCoronalPlaneRep3dc.h"
#include "vtkLight.h"
//#include "misGpuSagittalPlaneRep3dc.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
//#include "mismultiplanerep.h"
#include "misGpuAxialMultiplaneRepresentation.h"
#include "misMultiplaneImageViewer.h"
#include "mis3dTexture.h"
#include "misGpuSagittalMultiplaneRepresentation.h"
#include "transfuncintensity.h"
#include "voreenapplication.h"
#include "misDIRReader.h"
#include "misGpuCoronalMultiplaneRepresentation.h"
#include "misImageGeoProperties.h"
#include "transfuncmappingkey.h"
#include "vtkImageReader.h"
#include "vtkimageCast.h"
#include "vtkTimerLog.h"
#include "misMacros.h"
#include "init.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misTextureStrcts.h"
#include "misApplicationSetting.h"
#include "misTransFunctionBuilder.h"
#include "misStrctColorData.h"
#include "misObjectPropertiesStruct.h"
#include "misImageToTextureMap.h"
#include "misOpenglTexture.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misDeformSliceRepTest
{
public:
	int m_Type;
	double  slice;
	double  pos[3];
	GLuint tf_id;
	typedef misDeformSliceRepTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   
	misGpuAxialMultiplaneRepresentation::Pointer  MultiPlane;
	//	misGpuSagittalMultiplaneRepresentation::Pointer MultiPlane;
	//	misGpuCoronalMultiplaneRepresentation::Pointer MultiPlane;
	misMultiplaneImageViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;
	misObjectProperties							m_ObjectProperties;
	double										defaultThreshold ;
	TransFuncIntensity*					m_transfunc;
	misApplicationSetting*						m_AppSetting;
	misVolumeDataDependensies		m_volumeStructData;
	tgt::Texture	 *							m_ColorMapTexture;

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

	misDeformSliceRepTest(int type)
	{
		m_Type=type;
		slice=100;
		int *size;

		this->m_PulseGenerator=igstk::PulseGenerator::New();
		m_PusleObserver=ObserverType::New();
		m_PusleObserver->SetCallbackFunction(this,&misDeformSliceRepTest::Render);
		this->m_PulseGenerator->AddObserver(igstk::PulseEvent(),m_PusleObserver);
		LoadGui();
		

		this->m_wnd->set_m_Handle((HWND)windowMain.Handle());
	

		this->m_wnd->GenerateRenderWindow();
		this->m_wnd->FPSDisplayOn();
		this->m_wnd->AddFPSRenderer();
		//RAMA
		int argc = 1;
		char* argv[1];
		argv[0] = "rama";
		tgt::init(tgt::InitFeature::ALL);
		tgt::initGL(tgt::InitFeature::ALL);


		//     this->m_cbk->m_RenderWindow=this->m_wnd->GetRenderWindow();
		this->m_Viewer=misMultiplaneImageViewer::New();
		this->m_Viewer->SetRenderer(m_wnd);
		m_Viewer->SetCamerSettingInternaly(true);
		//-------------------------
		vtkRenderer *rendere=this->m_Viewer->GetRenderer();
		misImageRenderer* pRendere=dynamic_cast<misImageRenderer*>(rendere);

		//pRendere->SetSortForALphaRendering(true);
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



		//-------------------------
		//this->m_wnd->GetRenderer()->SetBackground(0.2,1,1);

		this->m_PulseGenerator->RequestSetFrequency(20);
		this->m_PulseGenerator->RequestStart();

		this->AddImage();
	}
	misOpenglTexture*		m_FixedTexture;
	misOpenglTexture* 		m_MovingTexture;
	void AddImage()
	{

		MultiPlane = misGpuAxialMultiplaneRepresentation::New("ct");

		AddImage1();
		
		misImage*  pMisImage = dynamic_cast<misImage*>(m_pImage1);
		misImageToTextureMap*	TextureHandler = misImageToTextureMap::GetInstance();
		misOpenglTexture * imageTexture = TextureHandler->LookUpTexture(pMisImage);
		MultiPlane->SetTexture(imageTexture);
		MultiPlane->SetVisibilityOfMainTexture(FirstImage,true);
		MultiPlane->SetIsAlphaSetForBlending(1.0);

		this->m_Viewer->AddRepresentation(MultiPlane);
		this->m_Viewer->Render();
		slice = 50;
	}
	vtkImageData *m_pImage1,*m_pImage2;
	void AddImage1() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("D:\\Dicom Data\\Safarkhani Ghorban\\MRI\\DICOM\\PA000000\\ST000000\\SE000001");
		
		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage1=  m_pDicomReader->Get3DImageData(adrees); */

	}

	void Render()
	{

		this->m_Viewer->Render();
		slice=slice+1;
		MultiPlane->SetSliceNumber(slice);
		MultiPlane->UpdateCorrelated();

		if (slice>200)
			slice=0;
	}
	
	~misDeformSliceRepTest(void)
	{
	}
};

