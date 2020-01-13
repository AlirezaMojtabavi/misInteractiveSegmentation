#pragma once
#include"point.h"
#include "IRepresentation.h"
#include "misCameraInteraction.h"

class ConvertMousexyToWorldCoordinate
{
public:
	ConvertMousexyToWorldCoordinate(	std::shared_ptr<ICornerProperties> cornerProperties, std::shared_ptr<misCameraInteraction> cameraInteraction);
	void SetMainRepresentation(std::shared_ptr<IRepresentation> representation);

	parcast::PointD3  	CalculateNewPosition(vtkRenderWindowInteractor * interactor);
private:
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<misCameraInteraction> m_CameraService;
};

