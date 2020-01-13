#pragma once

#include "misVolumeSlicer.h"

class   misImageViewerObserver : public vtkCommand
{
private:
	misVolumeSlicer* m_Viewer;

public:

	static misImageViewerObserver* New()
	{return new misImageViewerObserver;}

	void SetViewer(misVolumeSlicer* imgViewer);

	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	misImageViewerObserver(void);
	~misImageViewerObserver(void);

};
