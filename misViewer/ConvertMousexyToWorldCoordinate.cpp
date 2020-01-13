#include "stdafx.h"
#include "ConvertMousexyToWorldCoordinate.h"
#include "misPlanarRepresentation.h"
#include "misSimplePointType.h"


ConvertMousexyToWorldCoordinate::ConvertMousexyToWorldCoordinate(std::shared_ptr<ICornerProperties> cornerProperties, std::shared_ptr<misCameraInteraction> cameraInteraction)
	:m_Cornerproperties(cornerProperties), m_CameraService(cameraInteraction)
{
}

void ConvertMousexyToWorldCoordinate::SetMainRepresentation(std::shared_ptr<IRepresentation> representation)
{
	m_MainRepresentation = representation;
}

parcast::PointD3 ConvertMousexyToWorldCoordinate::CalculateNewPosition(vtkRenderWindowInteractor * interactor)
{
	auto  gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return {};
	int x = 0;
	int y = 0;
	interactor->GetEventPosition(x, y);
	vtkRenderer* pRenderer = interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	pRenderer->SetDisplayPoint(x, y, 0);
	pRenderer->DisplayToWorld();
	auto position = pRenderer->GetWorldPoint();
	double* cameraRange = m_CameraService->GetCamera()->GetClippingRange();
	const double distanceToPlane = m_Cornerproperties->GetCameraDistanceToPlane();
	double Distance = (distanceToPlane - cameraRange[0]);
	auto planeNorm = m_Cornerproperties->GetPlaneNormal();
	misSimplePointType wordPosition;
	wordPosition.SetPoint(position);
	planeNorm.Normalize();
	planeNorm.Multiply(-Distance);
	wordPosition.Sum(planeNorm);
	wordPosition.GetPoint(position);
	double bounds[6];
	gpu2DRep->GetBoundingBox(bounds);
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
