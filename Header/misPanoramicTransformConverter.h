#pragma once

#include "IPanoramicCoordinatesConverter.h"
#include "IPanoramicTransformConverter.h"

// The misPanoramicTransformConverter class implements the IPanoramicTransformConverter interface. It computes the panoramic space
// transform as described in the interface document. The computed transform is orthogonal (not skewed).
// Conversion from image to panoramic space:
// The conversion in each direction is done by transforming points (0, 0, 0), (1, 0, 0), and (0, 0, 1) using the input transform
// and then converting coordinates to the destination coordinates. The three points are used to create unit vectors of the 
// object transform in the destination space (by subtracting points and normalizing). The third orthogonal unit vector is
// computed as the cross product of the first two in the order required by the right-handed coordinate system.
// the rotation part of the transform is created using the three unit vectors and the translation part comes from the converted
// point (0, 0, 0).
// If the source and destination spaces are the same (both are panoramic or image), the output transform will be identical 
// to the input transform.
// Coordinate conversions between panoramic and image space are performed using an instance of IPanoramicCoordinatesConverter.
class misPanoramicTransformConverter : public IPanoramicTransformConverter
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<ITransform> CreateTransform(const double matrixElements[16]) const;
	};
	
	misPanoramicTransformConverter(
		std::shared_ptr<IPanoramicCoordinatesConverter> coordConv, std::shared_ptr<Injector> injector = nullptr);

	// IPanoramicTransformConverter interface:
	virtual void SetTransformInImageSpace( std::shared_ptr<const ITransform> objectTransform ) override;
	virtual void SetTransformInPanoramicSpace( std::shared_ptr<const ITransform> objectTransform );
	virtual std::shared_ptr<ITransform> GetTransformInImageSpace() const;
	virtual std::shared_ptr<ITransform> GetTransformInPanoramicSpace() const override;

private:
	typedef itk::Vector<double, 3> VectorType;

	// Specifies any of the coordinate systems that can be used as the source of conversion.
	enum CoordinateSystem
	{
		CS_IMAGE,
		CS_PANORAMIC
	};

	// Transform the specified point using the input transform to get the point in the panoramic space
	itk::Point<double, 3> TransformAndConvertPointFromPanoramicToImage(double x, double y, double z) const;
	itk::Point<double, 3> TransformAndConvertPointFromImageToPanoramic(double s, double zp, double n) const;

	std::shared_ptr<Injector> m_Injector;
	vtkSmartPointer<vtkParametricSpline> m_CurveSpline;	// See SetXYSplineCurve
	
	// The input transform is stored in m_InputTransform no matter which coordinate system is the source of conversion. The
	// source coordinate system of the conversion is stored in m_SourceCoordinateSystem base on which one of SetTransform*
	// methods have most recently been used. This way, only one transform is kept at any time and consistency is ensured between
	// calls to different SetTransform* and GetTransform* methods.
	std::shared_ptr<const ITransform> m_InputTransform;	
	CoordinateSystem m_SourceCoordinateSystem;

	PointType m_ImageDimensions;	// See SetImageDimensions
	std::shared_ptr<IPanoramicCoordinatesConverter> m_PanoramicCoordinatesConverter;
};