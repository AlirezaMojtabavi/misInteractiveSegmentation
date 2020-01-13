#pragma once
#include "vtkPoints.h"
#include "vtkIdList.h"
#include "vtkRenderer.h"
#include "vtkPointPicker.h"
#include "igstkLogger.h"
#include "igstkLandmark3DRegistration.h"
#include "igstkEvents.h"
#include "igstkTransform.h"
#include "igstkCoordinateSystemTransformToResult.h" 
#include "vtkCamera.h"
#include "vtksphereSource.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkMath.h"
#include "vtkcommand.h"
#include "vtkTextActor3D.h"
#include "misSurfacePointPicker.h"
#include "misVolumePointPicker.h"
#include "mis3DLandmarkViewer.h"
  
class MISDLLEXPORT misHybridInteractionObserver : public vtkCommand

{

private:

	mis3DViewer::Pointer  m_pViewer;
	//bool m_SelctionMode;
	vtkRenderer*  m_renderer;
	string m_Text;
public:

//	bool SelctionMode() const { return m_SelctionMode; }
//	void SelctionMode(bool val) { m_SelctionMode = val; }
 

	std::string Text() const { return m_Text; }
	void Text(std::string val) { m_Text = val; }
	mis3DViewer::Pointer Viewer() const { return m_pViewer; }
	void Viewer(mis3DViewer::Pointer val);
	vtkRenderer* Renderer() const { return m_renderer; }
 
	static misHybridInteractionObserver *New()   { return new misHybridInteractionObserver; }
 	misHybridInteractionObserver();

	~misHybridInteractionObserver();

	 
	  std::vector<vtkActor*>  m_Landmarrks;
 
 
public:

	vtkIdList* PointID;
	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);
};


