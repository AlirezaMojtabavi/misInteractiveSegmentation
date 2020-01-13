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
#include "misApplicationSetting.h"
#include "misVoreenViewer.h"
#include "vtkImageShiftScale.h"
#include "vtkimageCast.h"
#include "misImageToTextureConvertor.h"
#include "misOpenglTexture.h"
#include "misTransFunctionBuilder.h"
#include "init.h"
#include "misObjectPropertiesStruct.h"

typedef itk::Point<float ,3>  PointType;

class misVoreenRepTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misVoreenRepTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   
	float bonethresholdvalue;
	float skinthresholdvalue;
	misVoreenViewer::Pointer   m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	void LoadGui();

	void LoadExtensions(
		vtkRenderWindow *window);

	//==========================================================================
	misVoreenRepTest(int type);
	
	std::shared_ptr<misImage> m_pImage;
	misImage* m_ShiftScaled_Image;
	misVoreenRepresentation::Pointer  pVorreen;
	float CameraRadius;
	float alpha;
	void AddImage();

	void Render();

	~misVoreenRepTest(void)
	{
	}
	misObjectProperties m_ObjectProperties;
	double defaultThreshold ;
	misApplicationSetting* m_AppSetting;
	misVolumeDataDependensies m_volumeStructData;

	void OnTreeViewClicked();
	void showshiftscaledvolume();
	void showSkinAtFirst();
	void UpdateVolume();
	void OnDeny();
	void RemoveAll();
	void ChangeOpacity(double i);

};


