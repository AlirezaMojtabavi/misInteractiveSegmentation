#pragma once

#include "misHeader.h"
#include "misImageViewer.h"

class misSyncronViwer;
class vtkCommand;



//set Current image position 4  view after clicking  a point on image  with leftbutton press  event 
class MISDLLEXPORT  misPointSelctObserver :
	public vtkCommand
{

private:
	misImageViewer::Pointer  m_pViewer;
 public:

	 static misPointSelctObserver* New()
	 {return new misPointSelctObserver;}

	 misSyncronViwer* m_pNavigation;

	void SetViewer(misImageViewer::Pointer val) { m_pViewer = val; }
 
	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	misPointSelctObserver(void);
	~misPointSelctObserver(void);
};
