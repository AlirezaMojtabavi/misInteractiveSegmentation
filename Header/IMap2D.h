#pragma once

// The IMap2D provides an abstract interface for mapping 2D points from one space to another. Using this interface, a discrete
// set of mappings are provided through repeated calls to AddMapping. Then, to evaluate the mapped coordinates from source to
// destination, call SourceToDestination. To obtain the map in the reverse direction, call DestinationToSource. Implementations
// could provide different types of interpolation for evaluation of points where exact match is not found within the input set.
// Author: Mohsen Rahimimoghaddam
// Date: Jul 2016
template<typename T>
class IMap2D
{
public:
	typedef T ValueType;

	// Structure used to hold point 2D coordinates in any of the spaces. Individual coordinates are referenced by x or y.
	struct MapPoint2D
	{
		MapPoint2D() : x(ValueType()), y(ValueType()) { }
		MapPoint2D(ValueType initX, ValueType initY) : x(initX), y(initY) { }
		ValueType x, y;
	};

	// Add a single mapping relation by providing point coordinates in the source and destination space.
	virtual void AddMapping(const MapPoint2D &sourcePoint, const MapPoint2D &point2) = 0;

	// Obtains the mapped coordinates, in the destination space, for the specified coordinates within the source space.
	virtual MapPoint2D SourceToDestination(const MapPoint2D& point, const MapPoint2D& valueIfNotFound = MapPoint2D()) const = 0;

	// Obtains the mapped coordinates, in the source space, for the specified coordinates within the source space.
	virtual MapPoint2D DestinationToSource(const MapPoint2D& point, const MapPoint2D& valueIfNotFound = MapPoint2D()) const = 0;
};