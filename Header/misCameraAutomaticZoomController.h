#pragma once

#include "misCameraAutomaticZoomControllerProperties.h"
#include "misObject.h"

// The misCameraAutomaticZoomController class provides a decorator around a vtkCamera object to enable automatic zooming. The 
// automatic zooming feature is based on a set of points supplied to the misCameraAutomaticZoomController object as coverage 
// points. The misCameraAutomaticZoomController object uses these points and changes the vtkCamera object zoom so that the camera
// view covers all the referenced points and allows for an extra margin which can be changed. The zoom level is changed through 
// the view angle of the vtkCamera object principally, and contingently through changing of its distance.
// Note: The object does not make any change to the underlying camera object until a call to UpdateZoom() is made.
class misCameraAutomaticZoomController :
	public misObject
{
	misObjectMacro(misCameraAutomaticZoomController, misObject);
	misObjectNewMacro(misCameraAutomaticZoomController);

public:
	// Type of the points used for coverage set.
	typedef itk::Point<double, 3> PointType;
	typedef std::list<PointType> PointListType;

	// Pointer to the vtkCamera object whose zoom is controlled by this controller.
	misPrivateVariableWithPublicAccessorsMacro(vtkSmartPointer<vtkCamera>, m_ControlledCamera, ControlledCamera);

	// Set of points to be used in determination of the zoom level according to class definition.
	misPrivateVariableWithPublicAccessorsMacro(PointListType, m_CoveragePoints, CoveragePoints);

	// Sets/gets the object holding the collection of properties and settings of the zoom controller. These are parameters that
	// affect behaviour of the zoom controller in a lot of different ways.
	void SetProperties(const misCameraAutomaticZoomControllerProperties &newProperties);
	const misCameraAutomaticZoomControllerProperties &GetProperties() const;

	// Update the zoom level of the underlying vtkCamera object based on the previously set coverage points and camera 
	// configuration. It changes the zoom level by widening/narrowing the view angle of the camera, or moving the camera position
	// along the axis connecting it to the camera focal point.
	void UpdateZoom();

	virtual ~misCameraAutomaticZoomController(void);

protected:
	misCameraAutomaticZoomController(void);

	// Moves the camera position to make the focal distance specified. In the mean time it updates member variables.
	void MoveCameraPosition(double distance);

	// Moves the camera away from the focal point to place the specified point between the threshold point and focal point.
	// The position change is performed if the projection of the point on the camera axis is further away from the focal point than 
	// the threshold point. The by-product of this method is the projection of the point on the camera axis.
	void MoveCameraIfTooClose(const double *point, double * pointProjection);
	
	// Recalculate camera parameters used internally by the class. This must be called if the threshold ratio or camera parameters
	// are modified outside the class.
	void CalculateParameters();

private:
	// The following parameters are updated by CalculateParameters()

	double m_CameraFocalPoint[3];	// Focal point of the camera, world coordinates
	double m_CameraPosition[3];	// Position of the camera, world coordinates
	double m_ThresholdPoint[3];	// Position of the threshold point on the camera axis, world coordinates. See MoveCameraIfTooClose()
	double m_CameraAxis[3];	// Axis of the camera, sometimes normalized, sometimes not.
	double m_ThresholdDistance;	// Distance from the focal point to the threshold point.
	misCameraAutomaticZoomControllerProperties m_Properties;	// See SetProperties()
};