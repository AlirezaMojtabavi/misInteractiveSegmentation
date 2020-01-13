#pragma once

#include "IBarycentricInterpolation.h"
#include "IMap2D.h"
#include "misDebug.h"

// The misMap2D class template provides an implementation for the IMap2D interface. This implementation provides 
// interpolation to evaluate point mappings that do not have an exact match within the input set.
template <typename T>
class misMap2D : public IMap2D<T>
{
public:
	misMap2D(std::shared_ptr<IBarycentricInterpolation<MapPoint2D, ValueType>> interpolation) 
		: m_XYMaxDistance(0), m_XpYpMaxDistance(0),
		m_Interpolation(interpolation)
	{
	}

	virtual void AddMapping( const MapPoint2D &sourcePoint, const MapPoint2D &destinationPoint ) override
	{
		PointListElement newPoint(sourcePoint.x, sourcePoint.y, destinationPoint.x, destinationPoint.y);
		for (int i = 0; i < m_AllPoints.size(); i++)
		{
			MapPoint2D currentSourcePoint(m_AllPoints[i].X, m_AllPoints[i].Y);
			MapPoint2D currentDestPoint(m_AllPoints[i].Xp, m_AllPoints[i].Yp);
			m_XYMaxDistance = std::max(std::sqrt(SquareDistance(sourcePoint, currentSourcePoint)), m_XYMaxDistance);
			m_XpYpMaxDistance = std::max(std::sqrt(SquareDistance(destinationPoint, currentDestPoint)), m_XpYpMaxDistance);
		}
		
		m_AllPoints.push_back(newPoint);
		m_XSortedIndex.clear();	// Invalidate existing sorted indexes
		m_XpSortedIndex.clear();
	}

	virtual MapPoint2D SourceToDestination(
		const MapPoint2D& point, const MapPoint2D& valueIfNotFound = MapPoint2D() ) const override
	{
		return PerformMapping(
			point, valueIfNotFound, SourceCoordSelector(), DestinationCoordSelector(), m_XYMaxDistance, m_XSortedIndex);
	}

	virtual MapPoint2D DestinationToSource(
		const MapPoint2D& point, const MapPoint2D& valueIfNotFound = MapPoint2D() ) const override
	{
		return PerformMapping(
			point, valueIfNotFound, DestinationCoordSelector(), SourceCoordSelector(), m_XpYpMaxDistance, m_XpSortedIndex);
	}

private:
	// A structure that represents each point mapped from source coordinate space to destination in 2D space
	struct PointListElement
	{
		PointListElement(T x, T y, T xp, T yp)
			: X(x), Y(y), Xp(xp), Yp(yp) { }
		
		PointListElement () {}
		
		// X in source space
		T X;
		
		// Y in source space
		T Y;
		
		// X in destination Space
		T Xp;

		// Y in Destination Space
		T Yp;
	};

	// Class for selecting the source Space elements of pointListElement
	class SourceCoordSelector
	{
	public:
		// For Source Space returns the X part of PointListElement
		ValueType X(PointListElement pointListElement) const { return pointListElement.X; }

		// For Source Space returns the Y part of PointListElement
		ValueType Y(PointListElement pointListElement) const { return pointListElement.Y; }
	};

	// Class for selecting the destination Space elements of pointListElement
	class DestinationCoordSelector
	{
	public:
		// For destination Space returns the X part of PointListElement
		ValueType X(PointListElement pointListElement) const { return pointListElement.Xp; }

		// For destination Space returns the Y part of PointListElement
		ValueType Y(PointListElement pointListElement) const { return pointListElement.Yp; }
	};

	// During the search for a point within a space, we need a Boundary for limiting and speeding up search process. 
	// By this structure we hold the left and right Boundary of search zone in vectors.
	struct Boundary
	{
		Boundary(int left, int right) : LeftBoundary(left), RightBoundary(right) { }

		// Right edge of Boundary
		int RightBoundary;

		// Left Edge of the Boundary
		int LeftBoundary;
	};

	// Calculate the mapped point in the space specified by destinationSelector from the point given in the space specified
	// by sourceSelector. Maximum distance between points in the source space and the sorted index of the points sorted by their
	// X component are required.
	template <class SourceCoordinateSelectorType, class DestinationCoordinateSelectorType>
	MapPoint2D PerformMapping(const MapPoint2D& point, const MapPoint2D& valueIfNotFound,
		const SourceCoordinateSelectorType& sourceSelector, const DestinationCoordinateSelectorType& destinationSelector,
		double maxDistance, std::vector<int>& sortedIndex) const
	{
		CreateSortedIndexForCoordinate(sortedIndex, sourceSelector);
		int xySearchZone = static_cast<int>(maxDistance / std::sqrt(static_cast<double>(m_AllPoints.size())));
		if(xySearchZone == 0)
			xySearchZone = 1;
		std::vector<MapPoint2D> currentTriangle;
		std::vector<MapPoint2D> currentTriangleValues;
		std::vector<int> searchZone;
		bool found = false;
		while (!found && xySearchZone <= maxDistance / 2)
		{
			searchZone = DefineSearchZone(xySearchZone, point, sortedIndex, sourceSelector);
			if(searchZone.size() > 0)
				currentTriangle = FindTheSmallestTriangle(point, searchZone, found, sourceSelector);
			xySearchZone *= 2;
		}
		if (!found)
			return valueIfNotFound;

		currentTriangleValues = FindValuesInZone(currentTriangle, searchZone, sourceSelector, destinationSelector);

		std::vector<ValueType> xValues;
		std::vector<ValueType> yValues;
		for (int i = 0; i < currentTriangleValues.size(); i++)
		{
			xValues.push_back(currentTriangleValues[i].x);
			yValues.push_back(currentTriangleValues[i].y);
		}
		m_Interpolation->SetTriangle(currentTriangle, xValues);
		auto finalPointX = m_Interpolation->Interpolate(point);
		m_Interpolation->SetTriangle(currentTriangle, yValues);
		auto finalPointY = m_Interpolation->Interpolate(point);
		return MapPoint2D(finalPointX, finalPointY);
	}

	// Calculate and returns the square of distance between 2 MapPoint2D
	double SquareDistance(const MapPoint2D &point1, MapPoint2D &point2) const
	{
		auto xDist = point1.x - point2.x, yDist = point1.y - point2.y;
		return xDist * xDist + yDist * yDist;
	}

	// Calculate and returns the square of distance between a PointListElement and a MapPoint2D and the pointListElement
	// elements is separated by CoordinateSelector that will be one of SourceCoordSelector or DestinationCoordSelector
	template <class CoordinateSelector>
	double SquareDistanceToElement(
		const PointListElement &point1, const MapPoint2D &point2, const CoordinateSelector &selector) const
	{
		auto dx = selector.X(point1) - point2.x;
		auto dy = selector.Y(point1) - point2.y;
		return (dx * dx + dy * dy);
	}

	// Sort the space points for desired space that is shown by coordinateSelector in template and store the result of sorting
	// for desired space with respect to X element of Space and stores to indexList
	template <class CoordinateSelector>
	void CreateSortedIndexForCoordinate(std::vector<int>& indexList, const CoordinateSelector &selector) const
	{
		if(indexList.size() > 0)
			return;

		indexList.resize(m_AllPoints.size());
		std::size_t n(0);
		std::generate(std::begin(indexList), std::end(indexList), [&n] { return n++; } );
		std::sort(std::begin(indexList), std::end(indexList),
			[&](int i1, int i2) { return selector.X(m_AllPoints[i1]) < selector.X(m_AllPoints[i2]); } );
	}

	//Find the smallest Triangle around the correntPoint
	template <class CoordinateSelector>
	std::vector<MapPoint2D> FindTheSmallestTriangle(
		const MapPoint2D &currentPoint, std::vector<int> searchZone, bool& found, const CoordinateSelector &selector) const
	{
		found = false;
		//find all distances to current point
		std::vector<double> distances;
		for (int i = 0; i < searchZone.size(); i++)
			distances.push_back(SquareDistanceToElement(m_AllPoints[searchZone[i]], currentPoint, selector));

		
		auto distanceSortedIndex = SortIndexes(distances);
		std::vector<MapPoint2D> candidatePoints;
		std::vector<bool> isVertexIncluded(searchZone.size(), false);
		std::fill(isVertexIncluded.begin(), isVertexIncluded.begin() + 3, true);

		do 
		{
			for (int i = 0; i < searchZone.size(); ++i) 
			{
				if (isVertexIncluded[i])
				{
					auto point = m_AllPoints[searchZone[distanceSortedIndex[i]]];
					candidatePoints.push_back(MapPoint2D(selector.X(point), selector.Y(point)));
				}
			}
			found = IsInsideTriangle(candidatePoints, currentPoint);
			if(found)
				break;
			candidatePoints.clear();
		} while (std::prev_permutation(isVertexIncluded.begin(), isVertexIncluded.end()));
		return candidatePoints;
	}

	// The point p is inside the triangle if 0 <= s <= 1 and 0 <= t <= 1 and s + t <= 1
	bool IsInsideTriangle(const std::vector<MapPoint2D> &points, const MapPoint2D& point) const
	{
		auto aPoint = MapPoint2D(0, 0);
		auto bPoint = MapPoint2D(points[1].x - points[0].x, points[1].y - points[0].y);
		auto cPoint = MapPoint2D(points[2].x - points[0].x, points[2].y - points[0].y);
		auto pPoint = MapPoint2D(point.x - points[0].x, point.y - points[0].y);

		auto d = bPoint.x * cPoint.y - cPoint.x * bPoint.y;

		auto omegaA = (pPoint.x * (bPoint.y - cPoint.y) + pPoint.y * (cPoint.x - bPoint.x) + 
			bPoint.x * cPoint.y - cPoint.x * bPoint.y) / d;
		auto omegaB = (pPoint.x * cPoint.y - pPoint.y * cPoint.x) / d;
		auto omegaC = (pPoint.y * bPoint.x - pPoint.x * bPoint.y) / d;

		if(omegaA >= 0 && omegaA <= 1 && omegaB <= 1 && omegaB >= 0 && omegaC >= 0 && omegaC <= 1)
			return true;
		return false;

	}

	// Here we search all of space that is represented by coordinateSelector in 2 sequence. The search procedure is limited
	// in X direction zoneDimension. After finding the proper X domain for this zoneDimension, then we sort the result with 
	// respect to Y direction coordinates and limit this direction also with zoneDimension, and the last result that is 
	// returned has the sorted indexes of points in m_AllPoints that is in the desired zone(zoneDimension).
	template <class CoordinateSelector>
	std::vector<int> DefineSearchZone(int zoneDimension, const MapPoint2D& currentPoint, 
		const std::vector<int>& sortexIndex, const CoordinateSelector &selector) const
	{
		auto xBoundary = FindBoundaryPoint(sortexIndex, zoneDimension, currentPoint, selector);

		auto first = sortexIndex.begin() + xBoundary.LeftBoundary;
		auto last = sortexIndex.begin() + xBoundary.RightBoundary;
		std::vector<int> xSearchZone(first, last);

		std::sort(xSearchZone.begin(), xSearchZone.end(),
			[&](int i1, int i2) 
		{ 
			return selector.Y(m_AllPoints[i1]) < selector.Y(m_AllPoints[i2]); 
		} );

		auto yBoundary = FindBoundaryPoint(xSearchZone, zoneDimension, currentPoint, selector);
		auto firstY = xSearchZone.begin() + yBoundary.LeftBoundary;
		auto lastY = xSearchZone.begin() + yBoundary.RightBoundary;

		std::vector<int> searchZone(firstY, lastY);
		return searchZone;
	}

	// Find the upper and lower boundary of data in data vector around the currentPoint in the zone that specified by 
	// zoneDimension and the space is specified by coordinateSelector.
	template <class CoordinateSelector>
	Boundary FindBoundaryPoint(
		const std::vector<int>& data, int zoneDimension, const MapPoint2D& currentPoint, const CoordinateSelector &selector) const
	{
		auto xDistance = [&](int i) { return std::abs(selector.X(m_AllPoints[i]) - currentPoint.x); };
		int left = std::find_if(data.cbegin(), data.cend(),
			[&](int i) { return xDistance(i) < zoneDimension; } ) - data.begin();
		int right = std::find_if(data.begin() + left, data.end(),
			[&](int i) { return xDistance(i) > zoneDimension; } ) - data.begin();
		return Boundary(left, right);
	}

	// Find the values of the destination SPace values for the given vector of points
	template <class SourceCoordinateSelectorType, class DestinationCoordinateSelectorType>
	std::vector<MapPoint2D> FindValuesInZone(const std::vector<MapPoint2D> &points, const std::vector<int> &zone, 
		const SourceCoordinateSelectorType &sourceSelector, const DestinationCoordinateSelectorType &destinationSelector) const
	{
		std::vector<MapPoint2D> values;
		
		for (int i = 0; i < points.size(); i++)
		{
			auto index = std::find_if(zone.cbegin(), zone.cend(),
				[&] (int j) { return (sourceSelector.X(m_AllPoints[j]) == points[i].x &&
						sourceSelector.Y(m_AllPoints[j]) == points[i].y);}) - zone.cbegin();
			auto point = m_AllPoints[zone[index]];
			values.push_back(MapPoint2D(destinationSelector.X(point), destinationSelector.Y(point)));
		}
		return values;
	}

	template <typename T>
	std::vector<size_t> SortIndexes(const std::vector<T> &v) const
	{
		// initialize original index locations
		std::vector<size_t> idx(v.size());
		std::size_t n(0);
		std::generate(std::begin(idx), std::end(idx), [&n] { return n++; } );

		// sort indexes based on comparing values in v
		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

		return idx;
	}

	// A vector for holding all the points that are ready for mapping
	std::vector<PointListElement> m_AllPoints;

	// a vector of sorted indexes of m_AllPoints with respect to x element of source space
	mutable std::vector<int> m_XSortedIndex;

	// a vector of sorted indexes of m_AllPoints with respect to x element of destination space
	mutable std::vector<int> m_XpSortedIndex;

	// Maximum distance between points in source space
	double m_XYMaxDistance;

	// Maximum distance between points in destination space
	double m_XpYpMaxDistance;

	//Interface to the interpolation calculator 
	std::shared_ptr<IBarycentricInterpolation<MapPoint2D, ValueType>> m_Interpolation;
};