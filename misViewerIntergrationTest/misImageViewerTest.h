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

#include "transfuncintensity.h"
#include "voreenapplication.h"
#include "misDIRReader.h"
#include "misImageGeoProperties.h"
#include "transfuncmappingkey.h"
#include "vtkImageReader.h"
#include "vtkimageCast.h"
#include "vtkTimerLog.h"
#include "misMacros.h"
#include "init.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misApplicationSetting.h"
#include "misTransFunctionBuilder.h"
//#include "misStrctColorData.h"
#include "misObjectPropertiesStruct.h"
#include "misVolumeData.h"
#include "misImageRenderer.h"
#include "misDICOMImageLoader.h"

typedef itk::Point<float ,3>  PointType;

class misImageViewerSimpleIntgTest
{
public:
	int m_Type;
	double  slice;
	double  pos[3];
	GLuint tf_id;
	typedef misImageViewerSimpleIntgTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   
	misPlanarRepresentation::Pointer  MultiPlane;
//	misGpuSagittalMultiplaneRepresentation::Pointer MultiPlane; o
//	misGpuCoronalMultiplaneRepresentation::Pointer MultiPlane;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;
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

	misImageViewerSimpleIntgTest(int type);
	misOpenglTexture*		m_FixedTexture;
	misOpenglTexture* 		m_MovingTexture;
	void AddImage();
	vtkSmartPointer<vtkImageData> m_pImage1, m_pImage2;
	void AddImage1() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:/Dicom data/Mohammad rostami/DICOM/PA1/ST1/SE1");
		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage1=  m_pDicomReader->Get3DImageData(adrees); */
		 
	}
	
	void AddImage2() 
	{
		misDIRReader* m_pDicomReader;
		m_pDicomReader= misDIRReader::New();
		PatientsContainerViewingTypdef   m_PatientTree;
		misDICOMImageLoader m_DICOMImageLoader;
		m_PatientTree = m_DICOMImageLoader.AnalyzeDirectoryToBuildPatientTree("F:/Dicom data/Mohammad rostami/DICOM/PA1/ST1/SE1");
		/*SeriAddress adrees;
		adrees = m_pDicomReader->GetSpecificSeriProperty(0,0 , 0);
		m_pImage2=  m_pDicomReader->Get3DImageData(adrees); */

	}
	void Render();

	void CreateTransferFunction()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		tgt::init();
		tgt::initGL();
		int argc = 1;
		char* argv[1];
		argv[0] = "rama";
		voreen::VoreenApplication* app = new voreen::VoreenApplication("simple-GLUT", "simple-GLUT", argc, argv,voreen::VoreenApplication::APP_ALL);
		app->init();
		app->initGL();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		double volumeThreshold;
		m_AppSetting = misApplicationSetting::GetInstance();
		this->m_ObjectProperties.ObjectRenderingType = misVolumeRendering;
		this->m_ObjectProperties.ObjectVolumeViewing = misSkinviewing;
  		this->m_ObjectProperties.ObjectColor.red = 255;
  		this->m_ObjectProperties.ObjectColor.blue = 0;
  		this->m_ObjectProperties.ObjectColor.green = 50;
  		this->m_ObjectProperties.ObjectColor.alpha = 255;
		if (CT == m_volumeStructData.parrentImagePointer->GetImageModality() )
		{
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForCT;		
		}
		else if (MRI == m_volumeStructData.parrentImagePointer->GetImageModality())
		{
			volumeThreshold = this->m_AppSetting->m_VisulaizationSetting.SkinThresholdForMRI;
		}
		else
			_ASSERT(true == false);

		this->m_volumeStructData.useable = true;
		if (0 == this->m_volumeStructData.objectPointer )
		{
			this->m_volumeStructData.objectPointer = std::make_shared<misVolumeData>();
		}
		this->m_volumeStructData.objectPointer->SetImageModality(m_volumeStructData.parrentImagePointer->GetImageModality());
		this->m_volumeStructData.objectPointer->SetMinThreshold(this->m_ObjectProperties.ObjectVolumeViewing,volumeThreshold);
	
		this->m_volumeStructData.objectPointer->SetObjectColor(this->m_ObjectProperties.ObjectVolumeViewing,this->m_ObjectProperties.ObjectColor);


		misTransFunctionBuilder			pTrasferfunction;
		misDoubleColorListTypedef opacityColorMappingLst =  m_volumeStructData.objectPointer->GetFinalOpacityColorMap(threeDimension);
		double* TableRange = m_MovingTexture->GetTableRange();
		if (TableRange)
		{
			m_transfunc = pTrasferfunction.GenerateTransferFunction(opacityColorMappingLst,TableRange);
			m_transfunc->updateTexture();
			m_transfunc->bind();
			m_ColorMapTexture = m_transfunc->getTexture();
		}
	}
	float First_Opacity;
	float Second_Opacity;
	void DecreaseFirstImageOpacity()
	{
		First_Opacity -=0.05;
		if (First_Opacity<0.0)
		{
			First_Opacity = 0.0;
		}
		Second_Opacity = 1 - First_Opacity;
		UpdateOpacity();
	}
	void IncreaseFirstImageOpacity()
	{
		First_Opacity +=0.05;
		if (First_Opacity>1.0)
		{
			First_Opacity = 1;
		}
		
		Second_Opacity = 1 - First_Opacity;
		 UpdateOpacity();
		
	}
	void UpdateOpacity()
	{
		MultiPlane->SetOpacityValueToTexture(FirstImage,First_Opacity);
		MultiPlane->SetOpacityValueToTexture(SecondImage,Second_Opacity);
	}
	void DecreaseSecondImageOpacity()
	{
		Second_Opacity -=0.05;
		if (Second_Opacity<0.0)
		{
			Second_Opacity = 0.0;
		}
		First_Opacity = 1 - Second_Opacity;
		UpdateOpacity();

	}
	void IncreaseSecondImageOpacity()
	{
		Second_Opacity +=0.05;
		if (Second_Opacity>1.0)
		{
			Second_Opacity = 1.0;
		}
		First_Opacity = 1 - Second_Opacity;
		UpdateOpacity();
	}

	~misImageViewerSimpleIntgTest(void)
	{
	}
};

