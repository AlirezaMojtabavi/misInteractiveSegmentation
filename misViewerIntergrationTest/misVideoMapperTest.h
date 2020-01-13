#pragma once


//misVideoMapperTest
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
#include "vtkTimerLog.h"
#include "mis3DViewer.h"
/*#include "misVideoRepresentation.h"*/
#include "misVideoTextureCreator.h"
/*#include "misImageVideoViewer.h"*/

typedef itk::Point<float ,3>  PointType;

class misVideoMapperTest
{
public:

	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misVideoMapperTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   

	//misImageVideoViewer::Pointer m_Viewer;
	std::shared_ptr<misVolumeSlicer>   m_Viewer;

	misDICOMImageLoader* m_DICOMImageLoader;
	vtkSmartPointer<vtkImageData> m_pImage1;
	misOpenglTexture*		imageTexure ;
	misVideoTextureCreator::Pointer m_VideoTextureCreator;
	void LoadGui();

	//==========================================================================
	misVideoMapperTest( );

	//==========================================================================
	void Render();


	~misVideoMapperTest(void);
	void LoadExtensions( vtkRenderWindow *window );
	std::wstring s2ws(const std::string& s);
	void TerminateCapture();
	void AddImageToScene();
};

