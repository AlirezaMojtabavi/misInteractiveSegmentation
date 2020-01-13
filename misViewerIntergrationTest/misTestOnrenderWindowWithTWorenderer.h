#pragma once


//misTestOnrenderWindowWithTWorenderer
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



class misTestOnrenderWindowWithTWorenderer
{
public:

	float  slice;
	double  pos[3];

	//		misImageInteractionStyle* pStyle;
	typedef misTestOnrenderWindowWithTWorenderer Self;
	igstk::PulseGenerator::Pointer  m_PulseGenerator;
	typedef itk::SimpleMemberCommand< Self >   ObserverType;
	ObserverType::Pointer     m_PusleObserver;
	misWindow m_wnd;
	misNativeWindow windowMain;   

	std::shared_ptr<I3DViewer>   m_Viewer[2];

	void LoadGui();

	//==========================================================================
	misTestOnrenderWindowWithTWorenderer( );

	//==========================================================================
	void Render();


	~misTestOnrenderWindowWithTWorenderer(void)
	{
	}
	void LoadExtensions( vtkRenderWindow *window );


};

