#pragma once
#include"point.h"
#include "IRepresentation.h"
#include "misCameraInteraction.h"
#include "I3DViewer.h"

class ConvertMousexyToWorldCoordinate
{
public:
	ConvertMousexyToWorldCoordinate(	std::shared_ptr<ICornerProperties> cornerProperties);
	void SetViewer(std::shared_ptr<I3DViewer> representation);

	parcast::PointD3  	CalculateNewPosition(vtkRenderWindowInteractor * interactor);
private:
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<misCameraInteraction> m_CameraService;

	std::shared_ptr<I3DViewer> m_3DViewer; // See SetMainRepresentation().
};

