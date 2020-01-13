#pragma once

#include "ITransform.h"

// The IPanoramicTransformConverter provides an abstract interface for converting transforms between the image coordinate system
// and a panoramic coordinate system defined using a spline. Since such a transform conversion is dependent on the translation 
// part of the source transform, it cannot be expressed in terms of a single transform matrix across the entire range of image 
// boundary. Therefore, you need to first set up the coordinate systems' mutual relations by specifying the panoramic curve 
// and image dimensions. 
// Then, to convert a transform from the image space to the panoramic space or the other way round, you should set transform
// in one of the coordinate systems using one of the SetTransform* methods and then get the converted transform in the other
// coordinate system using the opposite GetTransform* method. The computed transform should be considered valid for transforming 
// points near the origin. The object transform in each of the coordinate systems could be used for transforming a point or vector 
// in local object coordinate systems to its coordinates in the image or panoramic coordinate system.
// The panoramic coordinate system is defined such that the components of a transform within the panoramic space are as below:
// X translation: Distance along the curve (when displaced to contain the object position) corresponding to the object position.
// Y translation: Negative Z coordinate of the object position within the image space plus the image extent in the Z direction.
// Z translation: Amount to which the original curve must be displaced (along its normals at each point in the XY plane) to 
// contain the object position
// The three principal axes of the image coordinate system are related to the panoramic coordinate system at each point as below:
// The X axis is oriented along the tangent to the curve at the object position. Since the spline is within the XY plane, this axis 
// is perpendicular to image Z axis.
// The Y axis lies along the negative of the image Z axis (which is perpendicular to the panoramic X axis).
// The Z axis might be computed as the cross product of the unit vectors along X and Y axis to form a rectilinear coordinate
// system. On the other hand, a skewed coordinate system might be formed which might transform objects more accurately by
// having the Z axis lie along the positive Y axis in the image coordinate system.
class IPanoramicTransformConverter
{
public:
	typedef itk::Point<double, 3> PointType;	// Type used for representing spatial points

	// Sets the input transform for an object within the image coordinate system (that transforms the object coordinate system to
	// to that of the image). It could be the navigation tracker tool transform relative to the image or the plan transform ...
	virtual void SetTransformInImageSpace(std::shared_ptr<const ITransform> objectTransform) = 0;

	// Sets the input transform for an object within the panoramic coordinate system (that transforms the object coordinate 
	// system to to that of the panoramic view). It could be that of a point picked by the user, plan moved by the user.
	virtual void SetTransformInPanoramicSpace(std::shared_ptr<const ITransform> objectTransform) = 0;

	// Computes the equivalent of the input transform within the image coordinate system. Using this method, transform 
	// of a screw plan, placed on the panoramic view by user, can be computed in the image coordinate system and
	// used throughout the system.
	virtual std::shared_ptr<ITransform> GetTransformInImageSpace() const = 0;

	// Computes a transform that can be used for displaying the object (with the input transform within the image space) within
	// the panoramic view created using the curve.
	virtual std::shared_ptr<ITransform> GetTransformInPanoramicSpace() const = 0;

	virtual ~IPanoramicTransformConverter(void) { }
};