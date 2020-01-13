#include "StdAfx.h"
#include "misStageBase.h"

#include "misException.h"

misStageBase::misStageBase(void) 
	: m_Renderer(NULL),
	m_IsInitialized(false)
{
}


misStageBase::~misStageBase(void)
{
}

void misStageBase::Render()
{
	UpdateSpatialObjects();
	if (m_IsInitialized)
		m_Window.GetRenderWindow()->Render();
}

void misStageBase::Initialize( misRenderer::RendererType rendererType, HWND nativeWindowHandle )
{
	// Create and initialize the window object
	m_Window.set_m_Handle(nativeWindowHandle);
	m_Window.GenerateRenderWindow(Iwindows::NoViewer);

	InitializeRenderer(rendererType);

	m_IsInitialized = true;
}

void misStageBase::Initialize( misRenderer::RendererType rendererType, const misWindowModel &windowModel )
{
	m_Window.GenerateFormWindowModel(windowModel);
	m_Window.GenerateRenderWindow(Iwindows::NoViewer);

	InitializeRenderer(rendererType);

	m_IsInitialized = true;
}

void misStageBase::AddSpatialObject( misSpatialObject::Pointer spatialObject )
{
	if (!m_IsInitialized)
		throw misException("Attempt to add spatial object to stage in uninitialized state.");
	m_Renderer->AddSpatialObject(spatialObject);
}

void misStageBase::UpdateSpatialObjects()
{

}

vtkCamera* misStageBase::GetActiveCamera()
{
	if (!m_IsInitialized)
		throw misException("Attempt to add get stage active camera in uninitialized state.");
	return m_Renderer->GetRenderer()->GetActiveCamera();
}

void misStageBase::InitializeRenderer(misRenderer::RendererType rendererType)
{
	// Create and initialize the renderer object
	m_Renderer = misRenderer::New();
	m_Renderer->Initialize(rendererType);

	m_Window.AddRenderer(m_Renderer);	// Add the renderer to the window.
}

void misStageBase::SetClippingPlanes( double nearPlane, double farPlane )
{
	GetActiveCamera()->SetClippingRange(nearPlane, farPlane);
}

double misStageBase::GetWorldPointDifferentialInViewCoordinates( const double *worldPoint )
{
	double cameraPosition[3];
	GetActiveCamera()->GetPosition(cameraPosition);
	double pointViewAxis[3];	// Perspective line
	vtkMath::Subtract(worldPoint, cameraPosition, pointViewAxis);
	double unitXVector[] = { 1, 0, 0 };
	double gradientVector[3];
	vtkMath::Cross(pointViewAxis, unitXVector, gradientVector);
	vtkMath::Normalize(gradientVector);	// Gradient vector: a the unit vector perpendicular to perspective line
	double worldPoint2[3];
	vtkMath::Add(worldPoint, gradientVector, worldPoint2);	// The second point in world coordinates

	vtkSmartPointer<vtkCoordinate> coord1 = vtkSmartPointer<vtkCoordinate>::New();
	coord1->SetCoordinateSystemToWorld();
	coord1->SetValue(worldPoint[0], worldPoint[1], worldPoint[2]);	
	double *viewPoint1 = coord1->GetComputedDoubleViewportValue(m_Renderer->GetRenderer());	// First point in view port coordinates

	vtkSmartPointer<vtkCoordinate> coord2 = vtkSmartPointer<vtkCoordinate>::New();
	coord2->SetCoordinateSystemToWorld();
	coord2->SetValue(worldPoint2[0], worldPoint2[1], worldPoint2[2]);
	double *viewPoint2 = coord2->GetComputedDoubleViewportValue(m_Renderer->GetRenderer());	// Second point in view port coordinates

	double diff = std::sqrt(vtkMath::Distance2BetweenPoints(viewPoint1, viewPoint2));
	// Distance between the two points in view port coordinates.
	return diff;
}

void misStageBase::ConvertViewToWorldCoordinates( const double *viewPoint, double *worldPoint )
{
	vtkSmartPointer<vtkCoordinate> coord = vtkSmartPointer<vtkCoordinate>::New();
	coord->SetCoordinateSystemToView();
	coord->SetValue(viewPoint[0], viewPoint[1], viewPoint[2]);
	double *world = coord->GetComputedWorldValue(m_Renderer->GetRenderer());
	worldPoint[0] = world[0];
	worldPoint[1] = world[1];
	worldPoint[2] = world[2];
}
