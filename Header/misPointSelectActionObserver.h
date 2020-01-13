#pragma once

#include "misHeader.h"
#include "vtkCommand.h"
#include "misImageViewer.h"

//set Current image position 4  view after clicking  a point on image  with leftbutton press  event 
class MISDLLEXPORT  misPointSelectActionObserver : public vtkCommand
{

//private:
	misImageViewer::Pointer  m_pViewer;
public:

	static misPointSelectActionObserver* New()
	{return new misPointSelectActionObserver;}

	//misSyncronViwer* m_pNavigation;

	void SetViewer(misImageViewer::Pointer val) { m_pViewer = val; }

	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	misPointSelectActionObserver(void);
	~misPointSelectActionObserver(void);
};


