#include "StdAfx.h"
#include "misGeoActor.h"

misGeoActor::misGeoActor(void)
{
	m_DisbaleDepthDest=false;
}

misGeoActor::~misGeoActor(void)
{
}

misGeoActor* misGeoActor::New()
{
	return new misGeoActor;
}

bool misGeoActor::GetDisbaleDepthDest() const
{
	return m_DisbaleDepthDest;
}

void misGeoActor::SetDisbaleDepthDest( bool val )
{
	m_DisbaleDepthDest = val;
}
