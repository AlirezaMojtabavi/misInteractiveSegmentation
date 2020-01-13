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
//#include "misScrewSource.h"



class misScrewGenerationTest
{
public:

	double  height;
 	misScrewSource  generateScrew;

	//		misImageInteractionStyle* pStyle;
	typedef misScrewGenerationTest Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow wnd;
	misNativeWindow windowMain;   

	std::shared_ptr<I3DViewer>  m_Viewer;
	misImageCallback* imageClalback;
	//	misImageInteractorObserv *m_cbk;

	//misPlaneRepresentation::Pointer  m_pImageRep;
	int * m_Size;

	double sizeTool;

	void LoadGui();
	vtkPolyDataMapper *screwMapper;
	vtkSmartPointer<vtkPolyData> poly;
	//==========================================================================
	misScrewGenerationTest( );

	//==========================================================================
	void Render();


	~misScrewGenerationTest(void)
	{
	}
	void LoadExtensions( vtkRenderWindow *window );
	void extend(int state);

private:
	vtkActor* point1Actor;
	vtkActor* point2Actor;
};

 

