#include "stdafx.h"
#include "ConvertMousexyToWorldCoordinate.h"
#include "misPlanarRepresentation.h"
#include "misSimplePointType.h"


ConvertMousexyToWorldCoordinate::ConvertMousexyToWorldCoordinate(std::shared_ptr<ICornerProperties> cornerProperties)
	:m_Cornerproperties(cornerProperties)
{
}

void ConvertMousexyToWorldCoordinate::SetViewer(std::shared_ptr<I3DViewer> viewer)
{
	m_3DViewer = viewer;
}

parcast::PointD3 ConvertMousexyToWorldCoordinate::CalculateNewPosition(vtkRenderWindowInteractor * interactor)
{
	const auto bounds = m_3DViewer->GetBoundingBox();
	int x = 0, y = 0;
	interactor->GetEventPosition(x, y);
	vtkRenderer* pRenderer = interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	pRenderer->SetDisplayPoint(x, y, 0);
	pRenderer->DisplayToWorld();
	const auto position = pRenderer->GetWorldPoint();
	double* cameraRange = pRenderer->GetActiveCamera()->GetClippingRange();
	const double distanceToPlane = m_Cornerproperties->GetCameraDistanceToPlane();
	const double distance = (distanceToPlane - cameraRange[0]);
	auto planeNorm = m_Cornerproperties->GetPlaneNormal();
	misSimplePointType wordPosition;
	wordPosition.SetPoint(position);
	planeNorm.Normalize();
	planeNorm.Multiply(-distance);
	wordPosition.Sum(planeNorm);
	wordPosition.GetPoint(position);

	if ((position[0] > bounds[1]) || (position[1] > bounds[3]) || (position[2] > bounds[5]))
	{
		return {};
	}
	else if ((position[0] < bounds[0]) || (position[1] < bounds[2]) || (position[2] < bounds[4]))
	{
		return {};
	}
	return parcast::PointD3(position);
}
