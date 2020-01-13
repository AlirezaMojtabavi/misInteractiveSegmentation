#include "StdAfx.h"
#include "misBaseRenderer.h"

misBaseRenderer::~misBaseRenderer(void)
{
}

bool misBaseRenderer::GetUsingCulling() const
{
	return m_UsingCulling;
}

void misBaseRenderer::SetUsingCulling( bool val )
{
	m_UsingCulling = val;
}

misBaseRenderer::misBaseRenderer(void)
{
	m_UsingCulling=true;
	m_SortForALphaRendering=false;
	 
}


bool misBaseRenderer::GetSortForALphaRendering() const
{
	return m_SortForALphaRendering;
}

void misBaseRenderer::SetSortForALphaRendering( bool val )
{
	m_SortForALphaRendering = val;
}

void misBaseRenderer::SetFarPlane( double val )
{
	m_FarPlane = val;
}

void misBaseRenderer::SetNearPlane( double val )
{
	m_NearPlane = val;
}


 

 

