#pragma once

#include "IPointArrangementAlgorithm.h"

// The misPointArrangementAlgorithm class is an implementation of IPointArrangementAlgorithm that creates a vector from the 
// medial point of the input points to the criterion point (criterion vector), then vectors from the medial point to each of the 
// input points (radial vectors). It then creates iso-planar vectors (iso-planars) by cross multiplying each of the input 
// vectors by the criterion vector. Then it takes the first point in the input as the first one in the ordered output and uses its
// iso-planar as reference (reference). It calculates the angle between each of the iso-planars and the reference (0 ~ 180) and
// the sign of the angle is determined by the sign of ( reference x isoplanar ) . criterion (-180 ~ 180). Then it replaces negative
// angles with their equivalent from the range (180 ~ 360). Finally, it sorts the isoplanars according to their angles with the 
// reference and thus the output ordering of the points is determined.
class misPointArrangementAlgorithm : public IPointArrangementAlgorithm
{
public:
	misPointArrangementAlgorithm();
	~misPointArrangementAlgorithm();

	virtual void SetUnorderedPoints( const std::list<PointType> &points );
	virtual const std::list<PointType> & GetUnorderedPoints() const;

	virtual void SetCriterionPoint( const PointType &point );
	virtual const PointType & GetCriterionPoint() const;

	virtual std::vector<PointType> GetOrderedPoints();

private:
	typedef itk::Vector<double, 3> VectorType;

	// The InputPointData struct is used to internally store an input point and its related data that is calculated through the
	// processing step. The comparison operator is used afterwards for sorting points and putting them in the final order.
	struct InputPointData
	{
		InputPointData(const PointType &point) : m_Point(point) { }
		bool operator<(const InputPointData &other) const { return m_AngleWithReference < other.m_AngleWithReference; }
		PointType m_Point;	// The input point itself
		VectorType m_RadialVector;	// The vector from the medial point of all input points to the point itself.
		VectorType m_IsoPlanarVector;	// The cross product of the radial vector and the criterion vector.
		double m_AngleWithReference;	// The normalized angle between this isoplanar and the reference isoplanar. 
	};

	// Processes the input (unordered points and criterion point) and updates the internally kept ordered points.
	void ProcessInput();

	// Computes the mathematical average of the coordinates of all the input points (medial point) and creates the data structure
	// holding input unordered points and their related data.
	void ProcessUnorderedPoints();

	bool m_IsProcessingNecessary;	// Indicates whether the outputs points need to be reordered (when set input is set).
	PointType m_CriterionPoint;	// See SetCriterionPoint()
	std::list<PointType> m_UnorderedPoints;	// See SetUnorderedPoints()
	std::vector<PointType> m_OrderedPoints;	// See GetOrderedPoints

	std::vector<InputPointData> m_UnorderedPointsData;	// See ProcessUnorderedPoints()
	PointType m_MedialPoint; // See ProcessUnorderedPoints()
};

