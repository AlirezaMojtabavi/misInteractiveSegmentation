#pragma once
#pragma once


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

#include "vtkImageShiftScale.h"
#include "vtkimageCast.h"
#include "misImageToTextureConvertor.h"
#include "misOpenglTexture.h"
#include "misTransFunctionBuilder.h"
#include "init.h"
#include "misObjectPropertiesStruct.h"
#include "misDICOMImageLoader.h"


class misLineWidgetTest3d
{
public:
	int m_Type;
	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misLineWidgetTest3d Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	std::shared_ptr<Iwindows> m_wnd;
	misNativeWindow windowMain;   
	float bonethresholdvalue;
	float skinthresholdvalue;
	std::shared_ptr<mis3DVolumeRenderer>   m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	void LoadGui();
	void TSTDeleteRep();

	void LoadExtensions(
		vtkRenderWindow *window);

	//==========================================================================
	misLineWidgetTest3d();

	void AddSphere();

	void InitViewer();

	std::shared_ptr<misImage> m_pImage;


	float CameraRadius;
	float alpha;
	void AddVolume();

	void Render();
	misDICOMImageLoader* m_DICOMImageLoader;
	~misLineWidgetTest3d(void);
	void addWidget();
	misObjectProperties m_ObjectProperties;
	double defaultThreshold ;
	misApplicationSetting* m_AppSetting;
	misVolumeDataDependensies m_volumeStructData;

};



