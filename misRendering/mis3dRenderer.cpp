#include "StdAfx.h"
#include "mis3dRenderer.h"

#define NEARCLIPINGRANGE 1
#define FARCLIPINGRANGE 5000

using namespace std;

// The misReserCameraObserver class observe vtkRendering whne resetting camera to reset clipping 
// range to predefined clippping range
class misReserCameraObserver: public vtkCommand
{
public:
	static misReserCameraObserver* New()
	{
		return new misReserCameraObserver;
	}
 
private:
	virtual void Execute(vtkObject *caller, unsigned long eventId,
		void *callData) 
	{
		if(caller)
		{
			vtkRenderer* renderer = dynamic_cast<vtkRenderer*> (caller);
			if (renderer)
				renderer->GetActiveCamera()->SetClippingRange(NEARCLIPINGRANGE, FARCLIPINGRANGE);
		}
	}

};

mis3dRenderer* mis3dRenderer::New()
{
	return new mis3dRenderer;
}
 
void mis3dRenderer::ComputeVisiblePropBounds(   double allBounds[6] )
{
	vtkRenderer::ComputeVisiblePropBounds(allBounds);
	for (int i = 0; i < 3; i++)
	{
		if (allBounds[i] < m_MinBoundingLimit)
			allBounds[i] = m_MinBoundingLimit;
		if (allBounds[2 * i + 1] > m_MaxBoundingLimit)
			allBounds[2 * i + 1] = m_MaxBoundingLimit;
	}
}

mis3dRenderer::mis3dRenderer( void )
{
	m_MinBoundingLimit = NEARCLIPINGRANGE;
	m_MaxBoundingLimit = FARCLIPINGRANGE;
	vtkSmartPointer<misReserCameraObserver> resetObserver = vtkSmartPointer<misReserCameraObserver>::New();
	AddObserver(vtkCommand::ResetCameraEvent, resetObserver);
	
}

 