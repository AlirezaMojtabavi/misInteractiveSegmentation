#pragma once

#include "VisualizationGeneralTypes.h"
#include "misQuadGeometry.h"
#include "misSimplePointType.h"
#include "misTexturePropertyStruct.h"
#include "BusinessEntities\Point.h"
#include "ImageBoundingProperty.h"

class IPanoramicCoordinatesConverter;
enum class DentalSurgeryType;

using namespace parcast;

class ICornerProperties
{
public:
	typedef itk::Point<double, 3> PointType;

	~ICornerProperties() = default;

	virtual bool GetValidity() = 0;
	virtual vtkMatrix4x4* GetTransform() const = 0;

	// Gets the transform matrix that translates a 3-D widget placed at the origin and aligned with the primary axes to the current
	// position and aligns it with current display vectors (view-up, view-side, normal). The alignment is done differently for 
	// each image orientation (axial, coronal, sagittal).
	virtual vtkMatrix4x4* GetWidgetTransform() = 0;

	virtual parcast::PointD3 GetWidgetPositionWithDistance(double distance) const = 0;

	// Gets the position of camera as a point traveling a certain distance along the plane normal from the current sight line
	// intersection point. See GetCameraDistanceToPlane(), See GetPlaneNormal(), See GetSightLineIntersectionPoint()
	virtual parcast::PointD3 GetCameraPosition() const = 0;

	// Gets the focal point of camera as a point traveling a certain distance along the plane normal from the current sight line
	// intersection point. See See GetPlaneNormal(), See GetSightLineIntersectionPoint()
	virtual parcast::PointD3 GetCameraFocalPoint() const = 0;

	// Gets the predefined perpendicular distance from the camera position to the plane.
	virtual double GetCameraDistanceToPlane() const = 0;

	// Gets the image bounds in world coordinates.
	virtual double* GetBounds() const = 0;

	// Gets the set of four points representing a square in space that corresponds to the current slice in coordinates normalized
	// with respect to image bounds. See GetBounds(), See GetPlanePoints().
	virtual std::vector<misSimplePointType> GetTexturePoints(IMAGEORIENTATION pOrientation) = 0;

	// Gets the set of four points representing a square in space that corresponds to the current slice. This is calculated 
	// according to input values position, orientation, obliqueness, and probe direction.
	virtual std::vector<misSimplePointType> GetPlanePoints(IMAGEORIENTATION pOrientation) = 0;

	// Gets the view-up vector to be set on the camera, that is the world coordinates unit vector which in the display coordinates 
	// should be in positive Y direction. Direction is defined by industry standards.
	virtual misSimplePointType GetPlaneViewUp() = 0;

	// Gets the plane normal vector, that is the world coordinates unit vector perpendicular to the slice plane whose direction
	// is defined by industry standards.
	virtual misSimplePointType GetPlaneNormal() = 0;

	// Gets the central point of the display square. See GetPlanePoints().
	virtual misSimplePointType GetPlaneCenter() = 0;

	// Gets the current slice number being displayed. This is calculated based on the current plane orientation, its distance
	// with the first slice and image spacing in the direction of plane normal. The first slice is the last one parallel to the 
	// current plane when advancing along the plane normal (towards the camera). The last one means planes beyond 
	// that are outside of image bounds. Directional spacing is calculated according to image spacing in each direction and
	// current plane normal direction.
	virtual int GetCurrentSliceNumber() = 0;

	// Gets total number of slices available in current plane direction. It is calculated as the distance between the first and
	// last planes (parallel to current plane) along the plane normal direction that have a non-null intersection with image 
	// bounds. See GetCurrentSliceNumber()
	virtual int GetMaxSliceNumber() = 0;

	// Gets the distance between the current image slice and the first image slice along the direction of current plane normal.
	// See GetCurrentSliceNumber()
	virtual double GetCurrentSlicePosition() = 0;

	// Gets the distance, in world measures, of two consecutive image slices along the direction of current plane normal direction.
	virtual double GetSliceSpacing() = 0;

	// Set the current position by navigating to a slice number. Effectively, this method moves the current position only along 
	// plane normal direction so that GetCurrentSliceNumber() is equal to the given slice number.
	virtual void SetPositionBySliceNumber(int newSliceNumber) = 0;

	// Gets the current position from which a slice of image is extracted. See SetCurrentPosition(), SetMatrix()
	virtual parcast::Point<double, 3> GetCurrentPosition() = 0;
	virtual PointType GetCurrentPositionPoint() const= 0;

	// Sets the current position on the matrix without altering the probe direction. See SetMatrix()
	virtual void SetCurrentPosition(const double* position) = 0;

	// Sets the current position and probe direction as a single transform matrix that translates the origin to the current 
	// position and aligns the Z axis with probe direction.
	virtual void SetMatrix(vtkMatrix4x4* pTrans) = 0;

	// Sets the image orientation to use for image slicing (axial, coronal, sagittal). When the oblique mode is activated, 
	// the probe direction is considered to be the coronal plane normal. Then, axial and sagittal planes are calculated with
	// regard to that. See related ViewSettings documents.
	virtual void SetOrientation(IMAGEORIENTATION pOrn) = 0;

	// Gets/sets whether the class is operating in oblique mode. If false (standard orientations should be used), the probe direction
	// is taken to be orthogonal to the coronal plane. Thus, setting SetupOrientation as AXIAL, CORONAL, or SAGITTAL will result
	// in the slice in the respective standard anatomical plane. If true, the a SetupOrientation of CORONAL will correspond to 
	// ProbeEye view while AXIAL and SAGITTAL orientations will result in AXIOCORONAL and CORONOSAGITTAL views containing the 
	// probe. See SetOrientation()
	virtual void SetObliqueMode(bool val) = 0;


	// Sets the camera sight line intersection point to the given point. This must be a point on the slice plane and on the line
	// connecting camera position to camera focal point. This point is used in panning.
	virtual void SetSightLineIntersectionPointTo(double position[3]) = 0;

	// Sets the camera sight line intersection point to slice plane centre. See SetSightLineIntersectionPointTo(),
	// See GetPlaneCenter()
	virtual void SetSightLineIntersectionPointToPlaneCenter() = 0;

	// Resets the camera sight line intersection point to current position. See SetSightLineIntersectionPointTo(),
	// See GetCurrentPosition()
	virtual void ResetSightLineIntersectionPoint() = 0;

	// Gets the camera sight line intersection point. See SetSightLineIntersectionPointTo(),
	virtual	misSimplePointType GetSightLineIntersectionPoint() = 0;

	// Set the properties of the image to be used for slicing.
	virtual void SetImageBounding(const ImageBoundingProperty& prop) = 0;

	virtual void Reset(void) = 0;

	// Get the image slice plane square as a misQuadGeometry object. See GetPlanePoints(), GetPlaneNormal().
	virtual misQuadGeometry GetImageSliceQuad() = 0;
	//apply an offset to  plane that render image 
	virtual void ApplyOfsset(double offset) = 0;
	virtual double GetImagePlaneOffset() const = 0;

	virtual void SetImageSliceViewerZoomFactor(double zoomFactor) = 0;

	virtual void SetDentalSurgeryType(DentalSurgeryType surgeryType) = 0;

	virtual void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter) = 0;
	virtual std::shared_ptr<const IPanoramicCoordinatesConverter> GetPanoramicCoordinateConverter() const = 0;

	virtual void SetPlanCentricViewAngle(double angle) = 0;
};