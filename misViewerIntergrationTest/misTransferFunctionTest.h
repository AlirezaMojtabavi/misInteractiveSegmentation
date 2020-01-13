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
#include "mis3dTexture.h"
#include "transfuncintensity.h"
#include "voreenapplication.h"
#include "misDIRReader.h"

#include "misImageGeoProperties.h"
#include "transfuncmappingkey.h"
#include "vtkImageReader.h"
#include "vtkimageCast.h"
#include "misTransferFunction.h"
#include "misImageToTextureMap.h"
#include "misOpenglTexture.h"
#include "init.h"
#include "texture.h"
#include "misDatasetIO.h"
#include "misImageByteAnalysis.h"
using namespace  tgt;

typedef itk::Point<float ,3>  PointType;

class misTransferFunctionTest
{
public:
	int m_Type;
	float  slice;
	double  pos[3];
	GLuint tf_id;
	//		misImageInteractionStyle* pStyle;
	typedef misTransferFunctionTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   
	misPlanarRepresentation::Pointer  MultiPlane;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;
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

	void OpacityUp()
	{
		segmentedOpacity+=0.1;
		if (segmentedOpacity>1.0)
		{
			segmentedOpacity = 1.0;
		}
		SetTransferFunction();
		this->MultiPlane->SetTransferFunctionID(tf_id);
	}

	misTransferFunctionTest(int type);
	//misRootVolumeTexture* m_FixedTexture;
	//misRootVolumeTexture *m_MovingTexture;
	vtkImageData * m_pImage;
	void AddImage();

	void Render();
	double TableRange[2];

	tgt::vec4 blackColor;
	void SetTransferFunction();
	TransFuncIntensity* transferFunc;
 
	double segmentedOpacity;
	void OpacityDown();
 
	void UpdateTransferFunction();

	~misTransferFunctionTest(void)
	{
	}
	GLuint volume_texture;
	
};

