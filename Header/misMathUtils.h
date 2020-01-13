#pragma once

#define PI 3.14159265358979f

#include "mis3DPoint.h"
#include "mis3dVector.h"
#include "vector.h"
#include "BusinessEntities/Vector.h"
#include <ExtLibWrappers/IPointListCodec.h>
class ITransform;
class misTransform;

class misRay
{
public:
	typedef itk::Vector<double,3> VectorType;

	misRay(VectorType p0,VectorType p1)
	{
		this->m_p0 = p0;
		this->m_p1 = p1;
	}
	VectorType m_p0;
	VectorType m_p1;
};

class misMathUtils
{
public:
	typedef mis3DPoint<double> PointType;
	typedef mis3DVector<double> VectorType;
	misMathUtils(void);
	~misMathUtils(void);

	//return projection of specified point on a line defined with 2 point (start point and end point)
	static PointType GetProjectedPointOnLine(const PointType& point, const PointType& startPoint, const PointType& endPoint);

	//Compute the projection of  given point on specified plane by a point and a normal
	static PointType GetProjectPointOnPlane( const PointType position, const PointType pointOnPlane, const VectorType planeNormal );

	// Gets the (unsigned) angle between two vectors in degrees in the range [0, 180)
	static double AngleBetween2Vectors(const VectorType &vec1, const VectorType &vec2);

	// Convert degrees into radians
	static double RadiansFromDegrees(double degrees);

	// Convert radians into degrees
	static double DegreesFromRadians(double radians);
	
	// Test approximate equality for floating point types since precise equality is not supported.
	static bool IsClose(double val1, double val2, double tolerance = 1e-6)
	{
		return (val1 - val2) * (val1 - val2) <= tolerance * tolerance;
	}

	// Test approximate equality for floating point combo types (vectors, points, ...) since precise equality is not supported.
	template <typename ComboType1, typename ComboType2>	// itk::Point, itk::Vector, ...
	static bool AreCoordinatesClose(ComboType1 point1, ComboType2 point2, double tolerance = 1e-6)
	{
		return IsClose(point1[0], point2[0], tolerance) &&
			IsClose(point1[1], point2[1], tolerance) &&
			IsClose(point1[2], point2[2], tolerance);
	}

	// Test approximate equality for floating point, one dimensional arrays of equal size (vectors, points, ...) since 
	// precise equality is not supported.
	template <int Size, typename ArrayType1, typename ArrayType2>	// double[N], std::vector<double>, itk::Point, itk::Vector, ...
	static bool AreArraysClose(ArrayType1 array1, ArrayType2 array2, double tolerance = 1e-6)
	{
		bool areClose = true;
		for (int i = 0; i < Size; i++)
			areClose = areClose && IsClose(array1[i], array2[i], tolerance);
		return areClose;
	}

	static bool AreVtkTransformsClose(
		vtkSmartPointer<vtkTransform> trans1, vtkSmartPointer<vtkTransform> trans2, double tolerance = 1e-6);

	// Gets the distance from the nearest point on the line line<l1,l2> to the point p.
	static double DistancePointFromLine(const PointType& p, const PointType& l1, const PointType& l2) ; 

	static void MergeBounding(double* bounding1, double* bounding2, double* outBounding );

	// Calculates projected position of a given point on a line in space defined by specifying Cartesian coordinates of two points
	// on it.
	static void ProjectPointOnLine(
		const double *linePoint1, const double *linePoint2, const double *otherPoint, double *projectedPoint);

	// Computes the the point positioned half-way between the two specified points.
	static void ComputeMidpoint(const double *point1, const double *point2, double *midPoint);

	// Computes and creates a transform to rotate a the source vector to align it with the destination vector. It is used by 
	// subclasses to put the guide props along the calculated directions.
	static vtkSmartPointer<vtkTransform> RotationTransformFromVectors(
		const double *sourceDirectionVector, const double *destinationDirectionVector);

	// Computes the angle, in degrees, between two vectors in the 3d space. Used by subclasses to perform compute the required 
	// transform for their props.
	static double ComputeAngleBetweenVectors(const double * vec1, const double * vec2);

	// Clips a value between a minimum and a maximum value. It returns the value if it is within the given range, min if
	// it is below the given minimum, and max if it is above the given maximum.
	template <class T>
	static const T& ClipValue(T inputValue, T min, T max)
	{
		return std::min(std::max(inputValue, min), max);
	}

	static double StdDeviation( std::vector<double> v, double ave );
	
	static bool FillMatrix(vtkMatrix4x4* matrix, double elements[3], int columnNumber);

	
	//Create a vtktransform form 16 elements(4*4 element of a matrix)
	static vtkSmartPointer<vtkTransform> CreateTransformFromMatrixElements(const double* elements);
	static vtkSmartPointer<vtkMatrix4x4> CreateMatrixFromMatrixElemnts(const double* elements);
	static tgt::Matrix4d CreateTgtMatrix4d(vtkSmartPointer<vtkMatrix4x4> vtkMat);
	static void FillElemetInMatrix(vtkMatrix4x4* matrix, double* newElemts, int replaceColumn);
	static double* GetCrossProduct(const double* FirstVector, const double* SecondVector);
	static void GetElementFormVtkTransform(vtkSmartPointer<vtkTransform> transform, double elements[16]);
	static void CopyMatrixElements(vtkSmartPointer<vtkMatrix4x4> transform, double elements[16]);
	static std::shared_ptr<misTransform> CreateTransform( vtkMatrix4x4* vtkMat );
	static std::shared_ptr<misTransform> CreateTransform(const igstk::Transform& igstkTrans);
	static vtkSmartPointer<vtkTransform> CreateVtkTransform(std::shared_ptr<const ITransform> trans);

	static parcast::PointD3 misMathUtils::GetIntersectionLineWithPlane(const parcast::VectorD3& normalPlane, const parcast::PointD3& startPointPlan
		, const parcast::PointD3 endPointPlan, const parcast::PointD3& currentPosition);
	static bool IsPerpendicular(const parcast::VectorD3& normalPlane, const parcast::PointD3& startPoint
		, const parcast::PointD3 endPoint);
};

