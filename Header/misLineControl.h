#pragma once

#include "VisualizationGeneralTypes.h"
#include "misSimplePointType.h"

class misLineControl
{
public:
	typedef itk::Vector<double, 3> VectorType;
	misLineControl();
	~misLineControl(void);

	double* GetAccuratePointOnLine(std::string pos, double movedPoint[3]);
	double* GetAccuratePointOnCircle(std::string pos, double movedPoint[3]);
	
	void SetMaxAllowedLineLen( double len );
	void SetPlaneNormal( misSimplePointType planeNorm );

	void InitLineValues( double p1[3], double p2[3] );
	void InitCircleValues( double p1[3], double p2[3]);
	
	void SetOrientation(IMAGEORIENTATION orientation);
	void GetAccuratePointsOnAxialView(std::string pos, double movedPoint[3], double accuratePoint[3]);

	void EnforceScrewLengthLimitation(std::string pos, double p1[3], double p2[3]);
private:
	double			m_MaxAllowedLineLen;
	double			m_Radius;

	misSimplePointType		m_Point1;
	misSimplePointType		m_Point2;
	misSimplePointType		m_OriginPoint1;
	misSimplePointType		m_OriginPoint2;

	misSimplePointType		m_LineNormal1;
	misSimplePointType		m_LineNormal2;
	misSimplePointType		m_PlaneNormal;

	IMAGEORIENTATION	m_Orientation;
};

