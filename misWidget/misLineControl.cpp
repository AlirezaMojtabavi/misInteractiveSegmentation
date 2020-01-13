#include "StdAfx.h"
#include "misLineControl.h"

using std::string;

misLineControl::misLineControl()
{
	this->m_MaxAllowedLineLen = 50.0;
}

misLineControl::~misLineControl(void)
{
}

void misLineControl::SetMaxAllowedLineLen( double len )
{
	this->m_MaxAllowedLineLen = len;
}

double* misLineControl::GetAccuratePointOnLine( std::string pos, double movedPoint[3] )
{
	auto funcPreoperation = [](misSimplePointType movedPoint, misSimplePointType originPoint, misSimplePointType lineNormal)-> double*
	{
		double distance = 0.0;
		movedPoint.Minus(originPoint);
		distance = movedPoint.GetLength();
		
		double* accuratePoint = new double[3];
		accuratePoint[0] = lineNormal[0] * distance + originPoint[0];
		accuratePoint[1] = lineNormal[1] * distance + originPoint[1];
		accuratePoint[2] = lineNormal[2] * distance + originPoint[2];
	
		return accuratePoint;
	};

	double lineLen = 0.0;
	double* accuratePoint = new double[3];
	
	misSimplePointType	tmpPoint;
	tmpPoint.SetPoint(movedPoint);
	
	if (pos == "OnP1")
	{
		accuratePoint = funcPreoperation(tmpPoint, m_OriginPoint2, m_LineNormal1);
		
		tmpPoint.SetPoint(accuratePoint);
		tmpPoint.Minus(m_OriginPoint2);
		lineLen = tmpPoint.GetLength();
		if (lineLen < m_MaxAllowedLineLen)
		{
			m_Point1.SetPoint(accuratePoint);
		}
		m_Point1.GetPoint(accuratePoint);
	}
	else if (pos == "OnP2")
	{
		accuratePoint = funcPreoperation(tmpPoint, m_OriginPoint1, m_LineNormal2);

		tmpPoint.SetPoint(accuratePoint);
		tmpPoint.Minus(m_OriginPoint1);
		lineLen = tmpPoint.GetLength();
		if (lineLen < m_MaxAllowedLineLen)
		{
			m_Point2.SetPoint(accuratePoint);
		}
		m_Point2.GetPoint(accuratePoint);
	}
	return accuratePoint;
}

void misLineControl::InitLineValues( double p1[3], double p2[3] )
{
	m_Point1.SetPoint(p1);
	m_OriginPoint1.SetPoint(p1);

	m_Point2.SetPoint(p2);
	m_OriginPoint2.SetPoint(p2);

	double tmpLineLen[3];
	tmpLineLen[0] = m_OriginPoint1[0] - m_OriginPoint2[0];
	tmpLineLen[1] = m_OriginPoint1[1] - m_OriginPoint2[1];
	tmpLineLen[2] = m_OriginPoint1[2] - m_OriginPoint2[2];
	m_LineNormal1.SetPoint(tmpLineLen);
	m_LineNormal1.Normalize();

	tmpLineLen[0] = m_OriginPoint2[0] - m_OriginPoint1[0];
	tmpLineLen[1] = m_OriginPoint2[1] - m_OriginPoint1[1];
	tmpLineLen[2] = m_OriginPoint2[2] - m_OriginPoint1[2];
	m_LineNormal2.SetPoint(tmpLineLen);
	m_LineNormal2.Normalize();
}

double* misLineControl::GetAccuratePointOnCircle( string pos, double movedPoint[3] )
{
	double* accuratePoint = new double[3];

	misSimplePointType	tmpPoint;
	tmpPoint.SetPoint(movedPoint);

	misSimplePointType tmpPlaneNormal;
	tmpPlaneNormal.SetPoint(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);
	
	if (pos == "OnP1")
	{
		tmpPoint.Minus(m_Point2);
		
		misSimplePointType projection = tmpPlaneNormal.PlaneProjection(tmpPoint);
		projection.Normalize();
		accuratePoint[0] = projection[0] * m_Radius + m_Point2[0];
		accuratePoint[1] = projection[1] * m_Radius + m_Point2[1];
		accuratePoint[2] = projection[2] * m_Radius + m_Point2[2];
	}
	else if (pos == "OnP2")
	{
		tmpPoint.Minus(m_Point1);

		misSimplePointType projection = tmpPlaneNormal.PlaneProjection(tmpPoint);
		projection.Normalize();
		accuratePoint[0] = projection[0] * m_Radius + m_Point1[0];
		accuratePoint[1] = projection[1] * m_Radius + m_Point1[1];
		accuratePoint[2] = projection[2] * m_Radius + m_Point1[2];
	}
	
	return accuratePoint;
}

void misLineControl::InitCircleValues( double p1[3], double p2[3] )
{
	m_Point1.SetPoint(p1);
	m_Point2.SetPoint(p2);

	m_Radius = m_Point1.EuclideanDistance(m_Point2);
}

void misLineControl::SetPlaneNormal( misSimplePointType planeNorm )
{
	m_PlaneNormal = planeNorm;
}

void misLineControl::SetOrientation( IMAGEORIENTATION orientation )
{
	m_Orientation = orientation;
}

void misLineControl::GetAccuratePointsOnAxialView(string pos, double movedPoint[3], double accuratePoint[3])
{
	misSimplePointType tmp;
	tmp.SetPoint(movedPoint);
	if (pos == "OnP1" &&  m_Point1 == tmp)
	{
		return;
	}
	else if (pos == "OnP2" && m_Point2 == tmp)
	{
		return;
	}
	
	double distance = m_Point1.EuclideanDistance(m_Point2);
	misSimplePointType tempNormal;
	tempNormal.SetPoint(m_PlaneNormal[0], m_PlaneNormal[1], m_PlaneNormal[2]);

	tempNormal.Multiply(-distance);
	tempNormal.Sum(tmp);

	if (pos == "OnP1")
	{
		m_Point2.SetPoint(tempNormal.data);
		m_Point2.GetPoint(accuratePoint);
		m_Point1.SetPoint(movedPoint);
	}
	else if (pos == "OnP2")
	{
		m_Point1.SetPoint(tempNormal.data);
		m_Point1.GetPoint(accuratePoint);
		m_Point2.SetPoint(movedPoint);
	}
}

void misLineControl::EnforceScrewLengthLimitation(string pos, double p1[3], double p2[3])
{
	misSimplePointType tmpP1, tmpP2;
	tmpP1.SetPoint(p1);
	tmpP2.SetPoint(p2);

	double len = misSimplePointType::EuclideanDistance(tmpP1, tmpP2);

	
	if (len > 100.0)
	{
		if (pos == "OnP1")
		{
			misSimplePointType lineNormal = misSimplePointType::Minus(tmpP1, tmpP2);
			lineNormal.Normalize();

			p1[0] = lineNormal[0] * 100.0 + p2[0];
			p1[1] = lineNormal[1] * 100.0 + p2[1];
			p1[2] = lineNormal[2] * 100.0 + p2[2];
		}
		else if (pos == "OnP2")
		{
			misSimplePointType lineNormal = misSimplePointType::Minus(tmpP2, tmpP1);
			lineNormal.Normalize();

			p2[0] = lineNormal[0] * 100.0 + p1[0];
			p2[1] = lineNormal[1] * 100.0 + p1[1];
			p2[2] = lineNormal[2] * 100.0 + p1[2];
		}
	}
}