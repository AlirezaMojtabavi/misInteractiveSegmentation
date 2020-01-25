#include "stdafx.h"
#include "PanImage.h"
#include "misSimplePointType.h"
#include "ICornerProperties.h"


PanImage::PanImage(std::shared_ptr<ICornerProperties> cornerproperties)
	:m_Cornerproperties(cornerproperties)
{
}


void PanImage::SetMainRepresentation(std::shared_ptr<misPlanarRepresentation> mainRep)
{
	m_MainRrepresenation = mainRep;
}

void PanImage::SetInteractor(vtkRenderWindowInteractor* interactor)
{
	m_RenderWindowInteractor = interactor;
}


void PanImage::Pan()
{
	if (!m_MainRrepresenation)
		return;

	misTexturePropertyStruct Prop = m_MainRrepresenation->GetImageProperties(FirstImage, MainImage);
	if (!Prop.IsValid())
		return;

	itk::Point<double, 3> panDestination, panOrigin;
	int x = 0, y = 0;
	int deltaX = 0, deltaY = 0;
	m_RenderWindowInteractor->GetEventPosition(x, y);
	if (m_LastMouseEventX == x && m_LastMouseEventY == y)
		return;
	if (!m_LastMouseEventX.is_initialized() && !m_LastMouseEventY.is_initialized())
	{
		m_LastMouseEventX = x;
		m_LastMouseEventY = y;
		return;
	}
	auto renderer = m_RenderWindowInteractor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	renderer->SetDisplayPoint(x, y, 0);
	renderer->DisplayToWorld();
	double* pos = renderer->GetWorldPoint();
	panDestination[0] = pos[0];
	panDestination[1] = pos[1];
	panDestination[2] = pos[2];
	renderer->SetDisplayPoint(m_LastMouseEventX.get(), m_LastMouseEventY.get(), 0);
	renderer->DisplayToWorld();
	pos = renderer->GetWorldPoint();
	panOrigin[0] = pos[0];
	panOrigin[1] = pos[1];
	panOrigin[2] = pos[2];
	m_LastMouseEventX = x;
	m_LastMouseEventY = y;
	// When panning starts at origin and ends in destination, in fact the camera must be moved in the opposite direction to mimic
	// the panning movement.
	itk::Vector<double, 3> panVector = panOrigin - panDestination;
	auto  previousSightLineIntersectionPoint = m_Cornerproperties->GetSightLineIntersectionPoint();
	itk::Point<double, 3> newSightLineIntersectionPoint;
	newSightLineIntersectionPoint = previousSightLineIntersectionPoint.GetItkPoint() + panVector;
	m_Cornerproperties->SetSightLineIntersectionPointTo(newSightLineIntersectionPoint.GetDataPointer());


}
