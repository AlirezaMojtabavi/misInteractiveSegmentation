 #pragma once
#include "misVolumeSlicer.h"
#include "misAutoMeasurment.h"
#include "IBackToPanMode.h"
#include "../misViewer/ConvertMousexyToWorldCoordinate.h"
#include "LandmarkDataAndType.h"
#include "ILandmarkViewer.h"


class Volume3DSelectActionLandamrk : public vtkCommand
{
public:
	static Volume3DSelectActionLandamrk* New();
	vtkBaseTypeMacro(Volume3DSelectActionLandamrk, vtkCommand);

	void Create(std::shared_ptr<ILandmarkViewer>, std::shared_ptr<I3DViewer>,
		std::shared_ptr<ICursorService>, 
		std::shared_ptr<ICornerProperties>,
		misVolumeRendererContainer::Pointer,
		std::shared_ptr<LandmarkDataAndType> landmarkData);
	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;
	void UpdateImageWithSelectedPoint(const double* position);

private:

	Volume3DSelectActionLandamrk();
	void CaptureLandmark(const double* position);
	std::shared_ptr<LandmarkDataAndType> m_LandmarkData;
	std::weak_ptr<ILandmarkViewer> m_landamrKviewer;
	std::weak_ptr<I3DViewer> m_3DViewer;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	int m_LastMouseEventX;
	int m_LastMouseEventY;
	misVolumeRendererContainer::Pointer m_DummyObject;
	std::shared_ptr<ICursorService> m_CursorService;
	std::unique_ptr<ConvertMousexyToWorldCoordinate> m_ConvertMouseXYToWorldCoordinate;
};

