#include "StdAfx.h"
#include "misCameraAutomaticZoomController.h"

#include "misMathUtils.h"

misCameraAutomaticZoomController::misCameraAutomaticZoomController(void)
{
}

misCameraAutomaticZoomController::~misCameraAutomaticZoomController(void)
{
}

void misCameraAutomaticZoomController::UpdateZoom()
{
	// We need to find such a view angle for the camera that all the coverage points fall within the view. To this end, for every
	// point, we find the minimum view angle required to put it on the edge of the view. The greatest of all the view angles will
	// be the resultant (final) view angle. We multiply the angle by a predefined ratio so the point yielding the greatest angle 
	// will not fall on the edge of the view.
	// In the mean time, if any of the points are positioned further away from the focal point than a predefined threshold (camera
	// is too near to the focal point), the camera is moved away from the focal point.
	// When the final angle is calculated, if it is below the predefined minimum, instead of instantly applying it, we move the
	// camera towards the focal point. If it is above the predefined maximum, instead of instantly applying it, we move the
	// camera away from the focal point. In such cases the angle calculation is performed again (up to a limited number of times).
	// If the angle within the acceptable range is finally achieved, it is applied.
	CalculateParameters();

	double finalViewAngle = 0, finalViewAngleInDegrees = 0;

	for (int i = 0; 
		(finalViewAngleInDegrees < m_Properties.GetMinimumAngle() || finalViewAngleInDegrees > m_Properties.GetMaximumAngle()) 
		&& i < m_Properties.GetMaximumAngleCalculationPasses(); i++)
	{
		std::for_each(m_CoveragePoints.cbegin(), m_CoveragePoints.cend(), [&] (PointType point)
		{
			// Position of each point is projected on the camera axis. The ratio of its distance from the point and its distance 
			// from the camera yields tangent of the view half angle for that point.
			double *pointElements = point.GetDataPointer();
			
			double pointProjection[3];	// Projection of the point on the camera axis is calculated by MoveCameraIfTooClose()
			MoveCameraIfTooClose(pointElements, pointProjection);

			double projectionDistanceToPoint = std::sqrt(vtkMath::Distance2BetweenPoints(pointProjection, pointElements));
			double projectionDistanceToCamera = std::sqrt(vtkMath::Distance2BetweenPoints(pointProjection, m_CameraPosition));
			double angle = 2 * std::atan(projectionDistanceToPoint / projectionDistanceToCamera);
			if (angle > finalViewAngle)
				finalViewAngle = angle;
		});

		finalViewAngleInDegrees = vtkMath::DegreesFromRadians(finalViewAngle * m_Properties.GetAngleRatio());

		if (finalViewAngleInDegrees < m_Properties.GetMinimumAngle())	// The view angle is too small, move camera closer
		{
			MoveCameraPosition(m_ControlledCamera->GetDistance() / m_Properties.GetDistanceModificationFactor());
		}

		if (finalViewAngleInDegrees > m_Properties.GetMaximumAngle())	// The view angle is too large, move camera farther away
		{
			MoveCameraPosition(m_ControlledCamera->GetDistance() * m_Properties.GetDistanceModificationFactor());
		}
	}

	if (finalViewAngleInDegrees > m_Properties.GetMinimumAngle() && finalViewAngleInDegrees < m_Properties.GetMaximumAngle())
	{
		m_ControlledCamera->SetViewAngle(finalViewAngleInDegrees);
	}
}

void misCameraAutomaticZoomController::MoveCameraPosition( double distance )
{
	if (distance > m_Properties.GetMaximumDistance() || distance < m_Properties.GetMinimumDistance())
		return;

	vtkMath::Normalize(m_CameraAxis);

	vtkMath::MultiplyScalar(m_CameraAxis, distance);
	vtkMath::Add(m_CameraFocalPoint, m_CameraAxis, m_CameraPosition);
	m_ControlledCamera->SetPosition(m_CameraPosition);	// Next move the camera itself

	m_ThresholdDistance = distance * m_Properties.GetThresholdRatio();
	vtkMath::MultiplyScalar(m_CameraAxis, m_Properties.GetThresholdRatio());
	vtkMath::Add(m_CameraFocalPoint, m_CameraAxis, m_ThresholdPoint);	// First move the threshold point for subsequent checks
}

void misCameraAutomaticZoomController::CalculateParameters()
{
	m_ControlledCamera->GetFocalPoint(m_CameraFocalPoint);
	m_ControlledCamera->GetPosition(m_CameraPosition);
	vtkMath::Subtract(m_CameraPosition, m_CameraFocalPoint, m_CameraAxis);
	vtkMath::MultiplyScalar(m_ThresholdPoint, m_Properties.GetThresholdRatio());
	vtkMath::Add(m_CameraFocalPoint, m_CameraAxis, m_ThresholdPoint);
	m_ThresholdDistance = std::sqrt(vtkMath::Distance2BetweenPoints(m_CameraFocalPoint, m_CameraPosition));
}

void misCameraAutomaticZoomController::MoveCameraIfTooClose(const double *point, double * pointProjection)
{
	misMathUtils::ProjectPointOnLine(m_CameraPosition, m_CameraFocalPoint, point, pointProjection);
	double distanceToFocalPoint = std::sqrt(vtkMath::Distance2BetweenPoints(pointProjection, m_CameraFocalPoint));
	double distanceToThreshold = std::sqrt(vtkMath::Distance2BetweenPoints(pointProjection, m_ThresholdPoint));
	if (distanceToFocalPoint > distanceToThreshold && distanceToFocalPoint > m_ThresholdDistance)	// Too close!
	{
		MoveCameraPosition(distanceToFocalPoint / m_Properties.GetThresholdRatio());
	}
}

void misCameraAutomaticZoomController::SetProperties( const misCameraAutomaticZoomControllerProperties &newProperties )
{
	m_Properties = newProperties;
}

const misCameraAutomaticZoomControllerProperties & misCameraAutomaticZoomController::GetProperties() const
{
	return m_Properties;
}
