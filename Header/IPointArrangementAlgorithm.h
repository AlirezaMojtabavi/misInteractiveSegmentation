#pragma once

#include "itkPoint.h"

// The IPointArrangementAlgorithm class provides an abstract interface to classes that implement the capability to receive an
// unordered list of points (itk::Point<double, 3>) and a criterion vector (itk::Vector<double, 3>) and put the points in a 
// certain order based on the given criterion vector.
class IPointArrangementAlgorithm
{
public:
	typedef itk::Point<double, 3> PointType;	// Used for the set of points.

	// Gets/sets the unordered list of points as input of the algorithm.
	virtual void SetUnorderedPoints(const std::list<PointType> &points) = 0;	
	virtual const std::list<PointType> &GetUnorderedPoints() const = 0;

	// Gets/sets the criterion vector which determines how the input points should be arranged.
	virtual void SetCriterionPoint(const PointType &points) = 0;
	virtual const PointType &GetCriterionPoint() const = 0;

	// Gets the list of points put in the calculated order (calculation performed if necessary).
	virtual std::vector<PointType> GetOrderedPoints() = 0;
};