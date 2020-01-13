#include "stdafx.h"
#include "misImageIOProperties.h"

void misImageIOProperties::Reset( void )
{
	NumberOfComponent = -1;
	for (int i = 0; i < 6; ++i)
		extent[i] = FOVExtent[i] = 0;

	for (int i = 0; i < 3; ++i)
		spacing[i] = 0;

	scalerType         = -1;
	fileDimensionality = -1;
}

misImageIOProperties::misImageIOProperties()
{
	this->Reset();
}

misROI misImageIOProperties::GetRoi() const
{
	return m_Roi;
}

void misImageIOProperties::SetRoi( const misROI& val )
{
	m_Roi = val;
}
