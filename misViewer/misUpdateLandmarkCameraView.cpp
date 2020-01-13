
#include "stdafx.h"
#include "misUpdateLandmarkCameraView.h"
#include "misCamera.h"
#include "BusinessEntities\Point.h"
#include "CameraPositionCalculator.h"
#include "CameraPositionCalculatorFactory.h"
#include "misApplicationSetting.h"

misUpdateLandmarkCameraView::misUpdateLandmarkCameraView(std::shared_ptr<I3DViewer> viewer,
                                                         double landmarkLableCameraDistance)
	:
	  m_Viewer(viewer),
	  m_LandmarkLableCameraDistance(landmarkLableCameraDistance)
{
}

void misUpdateLandmarkCameraView::Update(itk::BoundingBox<double, 3, double>::Pointer boundingBox,
	std::shared_ptr<ILandmarkPointerRepresentation> landmark)
{
	if (!landmark->IsValid())
	{
		return;
	}
	const auto cameraPosCalc = parcast::CameraPositionCalculatorFactory::Create(parcast::PointD3(boundingBox->GetMinimum().GetDataPointer()),
		parcast::PointD3(boundingBox->GetMaximum().GetDataPointer()), m_LandmarkLableCameraDistance, misApplicationSetting::GetInstance()->m_WorkflowButtonSet);
	double position[3];
	landmark->GetPosition(position);
	auto cameraPosition = cameraPosCalc->GetCameraPosition(parcast::PointD3(position));
	auto camera = m_Viewer->GetRenderer()->GetActiveCamera();
	camera->SetPosition(cameraPosition.Elements());
	camera->SetFocalPoint(position);
	camera->SetViewUp(0.0, 0.0, -1.0);

}
