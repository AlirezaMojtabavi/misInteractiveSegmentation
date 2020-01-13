#include "StdAfx.h"
#include "misImageViewerObserver.h"

#include "misAutoMeasurment.h"
#include "misCoreEvents.h"
#include "misDistributionEvent.h"
	
#pragma warning (disable : 4503)

void misImageViewerObserver::Execute(vtkObject *caller, unsigned long eventId, void* callData)
{
	_ASSERT(0 ==1);
}

void misImageViewerObserver::SetViewer( misVolumeSlicer* imgViewer )
{
	_ASSERT( 0 ==1);
	if (imgViewer)
	{
		this->m_Viewer = imgViewer;
	}
}

misImageViewerObserver::misImageViewerObserver( void )
{
	_ASSERT( 0 ==1);
	this->m_Viewer = 0;
}

misImageViewerObserver::~misImageViewerObserver( void )
{

}
