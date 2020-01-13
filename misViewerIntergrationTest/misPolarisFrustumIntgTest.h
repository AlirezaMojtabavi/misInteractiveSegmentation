#pragma once

#pragma once


//misPolarisFrustumIntgTest
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
#include "misIntegrationTestApplication.h"



class misPolarisFrustumIntgTest : public misIntegrationTestApplication
{

public:
	misPolarisFrustumIntgTest(int &argc, char ** argv);

	virtual void PulseHandler();
private:
	std::shared_ptr<I3DViewer> m_Viewer;
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<misSurfaceRepresentation> ReadSTL(std::string fileName);
};
