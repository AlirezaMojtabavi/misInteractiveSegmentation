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
#include "vtkLight.h"
#include "igstkPulseGenerator.h"
#include "misWindow.h"
#include "misNativeWindow.h" 
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "misImageGeoProperties.h"
//#include "misVoreenMapper.h"
#include "transfuncmappingkey.h"
#include "misVoreenRepresentation.h"
#include "misDIRReader.h"
#include "vtkImageData.h"
#include "prsDebugVariable.h"
#include "voreenapplication.h"
#include "misImageToTextureConvertor.h"
#include "misDICOMImageLoader.h"
#include "misImage.h"

class misVolumeCroppingTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];
	misDICOMImageLoader m_DICOMImageLoader;

	//		misImageInteractionStyle* pStyle;
	typedef misVolumeCroppingTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   

	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	void LoadGui();

	void LoadExtensions(
		vtkRenderWindow *window);
		vtkActor* pSphereActor;
	//==========================================================================
	misVolumeCroppingTest();
std::shared_ptr<misImage> m_pImage;
	
	void AddImageMr();
	void AddImageCT();

	float CameraRadius;
	float alpha;
  

	std::vector<TransFuncIntensity*> m_Transfers;

	std::vector<misOpenglTexture*> m_Textures;
	//void SetTransferFunctionanTranslationForCt( );
	//void SetTransferFunctionanTranslationForMr( );
	////==========================================================================
	void Render();


	~misVolumeCroppingTest(void)
	{
	}
};


