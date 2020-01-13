#pragma once
#include "misVolumeSlicer.h"
#include "misAutoMeasurment.h"
#include "IBackToPanMode.h"
#include "../misViewer/ConvertMousexyToWorldCoordinate.h"
#include "LandmarkDataAndType.h"


class PointSelectAction: public vtkCommand
{
public:

	PointSelectAction(std::shared_ptr<I3DViewer>, std::weak_ptr<IVolumeSlicer> slicer,
	                  std::shared_ptr<ICornerProperties>,
	                  vtkSmartPointer<misInteractorSTyleImageExtend>,
	                  std::shared_ptr<IBackToPanMode>, misVolumeRendererContainer::Pointer,
	                  std::shared_ptr<ICursorService>, std::shared_ptr<misCameraInteraction>, std::shared_ptr<LandmarkDataAndType> landmarkData);
	~PointSelectAction();
 	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;
	void UpdateImageWithSelectedPoint();
private:
	void BackToPanMode();
	void CaptureLandmark(const double* position);
	void UpdateImage(bool updateCamera/*=true*/);
	std::shared_ptr<LandmarkDataAndType> m_LandmarkData;
	std::weak_ptr<IVolumeSlicer> m_Slicer;
	vtkSmartPointer<misInteractorSTyleImageExtend> m_pImageStyle;
	std::weak_ptr<I3DViewer> m_3DViewer;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<misCameraInteraction> m_CameraService;
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	int m_LastMouseEventX;
	int m_LastMouseEventY;
	misVolumeRendererContainer::Pointer m_DummyObject;
	std::shared_ptr<ICursorService> m_CursorService;
	misGeneralToolbarState m_GeneralToolbarState;
	misMeasurment::Pointer m_MeasurmentService;
	std::shared_ptr<IBackToPanMode> m_backToPanMode;
	std::unique_ptr<ConvertMousexyToWorldCoordinate>  m_ConvertMouseXYToWorldCoordinate;
};

