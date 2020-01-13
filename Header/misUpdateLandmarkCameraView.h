#include "IUpdateLandmarkCameraView.h"
#include "IRepresentation.h"
#include "I3DViewer.h"

class misUpdateLandmarkCameraView : public IUpdateLandmarkCameraView
{
public:
	misUpdateLandmarkCameraView(std::shared_ptr<I3DViewer> viewer,
	                            double landmarkLableCameraDistance);
	void Update(itk::BoundingBox<double, 3, double>::Pointer, std::shared_ptr<ILandmarkPointerRepresentation>) override;
private:
	std::shared_ptr<I3DViewer> m_Viewer;
	double m_LandmarkLableCameraDistance = 0;
};

