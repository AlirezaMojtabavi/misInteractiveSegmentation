#include "StdAfx.h"
#include "misROI.h"
#include <xutility>

misROI::misROI(void)
	: m_Initialized(false), m_IsPermanent(false)
{
	std::fill(m_Data, m_Data + 6, 0);
}

misROI::misROI(const double* inData, bool isPermanent)
	: m_Initialized(true), m_IsPermanent(isPermanent)
{
	std::copy(inData, inData + 6, m_Data);
}

misROI::misROI( double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, bool isPermanent /*= false*/ )
	: m_Initialized(true), m_IsPermanent(isPermanent)
{
	m_Data[0] = xMin;
	m_Data[1] = xMax;
	m_Data[2] = yMin;
	m_Data[3] = yMax;
	m_Data[4] = zMin;
	m_Data[5] = zMax;

}

misROI::misROI( const int* inExtent, const double* spacing, bool isPermanent /*= false*/ )
	: m_Initialized(true), m_IsPermanent(false)
{
	m_Data[0] = inExtent[0] * spacing[0];
	m_Data[1] = inExtent[1] * spacing[0];
	m_Data[2] = inExtent[2] * spacing[1];
	m_Data[3] = inExtent[3] * spacing[1];
	m_Data[4] = inExtent[4] * spacing[2];
	m_Data[5] = inExtent[5] * spacing[2];
	m_Initialized = true;
}

misROI::~misROI(void)
{
}

const double* misROI::getData() const
{
	return m_Data;
}

void misROI::getData( double *data ) const
{
	std::copy(m_Data, m_Data + 6, data);
}

const double& misROI::operator[] ( int index ) const
{
	return m_Data[index];
}

double& misROI::operator[]( int index )
{
	return m_Data[index];
}

bool misROI::ContainsPoint( double x, double y, double z )
{
	if (!m_Initialized)
		return true;

	if (x < m_Data[0] || x > m_Data[1])
		return  false;
	if (y < m_Data[2] || y > m_Data[3])
		return  false;
	if (z < m_Data[4] || z > m_Data[5])
		return  false;

	return true;
}

bool misROI::IsInitilized() const
{
	return  m_Initialized;
}

void misROI::Initilized()
{
	m_Initialized = true;
}

bool misROI::IsPermanent() const
{
	return m_IsPermanent;
}

void misROI::SetPermanent( bool isPermanent )
{
	m_IsPermanent = isPermanent;
}

void misROI::ResetToZeroBase()
{
	m_Data[1] = m_Data[1] - m_Data [0];
	m_Data [0] = 0;
	m_Data[3] = m_Data[3] - m_Data [2];
	m_Data [2] = 0;
	m_Data[5] = m_Data[5] - m_Data [4];
	m_Data [4] = 0;


}

misROI misROI::Intersection( const misROI& roi ) const
{
	misROI  result;
	result[0] = std::max(this->m_Data[0] , roi[0]);
	result[1] = std::min(this->m_Data[1] , roi[1]);
	result[2] = std::max(this->m_Data[2] , roi[2]);
	result[3] = std::min(this->m_Data[3] , roi[3]);
	result[4] = std::max(this->m_Data[4] , roi[4]);
	result[5] = std::min(this->m_Data[5] , roi[5]);
	result.Initilized();
	return result;

}

double misROI::GetVolume() const
{
	return (m_Data[1] - m_Data[0]) * (m_Data[3] - m_Data[2]) * (m_Data[5] - m_Data[4]);  
}

bool misROI::IsValid() const
{
	if (!m_ExternalValidity)
		return false;
	bool validity = (m_Data[1] - m_Data[0] > 0) && (m_Data[3] - m_Data[2] > 0) && (m_Data[5] - m_Data[4] > 0);  
	return validity;
}

void misROI::SetValidity(bool value)
{
	m_ExternalValidity = value;
}

double misROI::GetWidth() const
{
	return m_Data[1] - m_Data[0];
}

double misROI::GetHeight() const
{
	return m_Data[3] - m_Data[2];
}

double misROI::GetDepth() const
{
	return m_Data[5] - m_Data[4];

}

tgt::Vector3d misROI::GetMinPoint() const
{
	tgt::Vector3d minPoint;
	minPoint[0] = m_Data[0];
	minPoint[1] = m_Data[2];
	minPoint[2] = m_Data[4];
	return minPoint;
}

tgt::Vector3d misROI::GetMaxPoint() const
{
	tgt::Vector3d maxPoint;
	maxPoint[0] = m_Data[1];
	maxPoint[1] = m_Data[3];
	maxPoint[2] = m_Data[5];
	return maxPoint;
}

tgt::Vector3d misROI::GetCenter()
{
	return (GetMaxPoint()+ GetMinPoint())* 0.5;
 }

void misROI::scale(double scale)
{
	auto center = GetCenter();
	auto minPt = GetMinPoint();
	auto maxPt = GetMaxPoint();
	auto centerToMin = minPt - center;
	auto centerTomax = maxPt - center;
	minPt = center + centerToMin * scale;
	maxPt = center + centerTomax * scale;
	m_Data[0] = minPt[0];
	m_Data[2] = minPt[1];
	m_Data[4] = minPt[2];
	m_Data[1] = maxPt[0];
	m_Data[3] = maxPt[1];
	m_Data[5] = maxPt[2];
	
}
