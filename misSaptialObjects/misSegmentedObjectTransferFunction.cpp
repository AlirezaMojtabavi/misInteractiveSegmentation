#include "StdAfx.h"
#include "misSegmentedObjectTransferFunction.h"
misSegmentedObjectTransferFunction::misSegmentedObjectTransferFunction()
{
	this->Reset();
}
void misSegmentedObjectTransferFunction::SetTf( std::shared_ptr<TransFuncIntensity> tf)
	
{
	m_Tf = tf;
	m_IDAssigned = true;
}

GLuint misSegmentedObjectTransferFunction::GetTfId()
{
	return  m_Tf->getTexture()->getId();
}

std::shared_ptr<TransFuncIntensity> misSegmentedObjectTransferFunction::GetTf() const
{
	return m_Tf;
}



bool misSegmentedObjectTransferFunction::GetAssigned()
{
	return  m_IDAssigned;

}



void misSegmentedObjectTransferFunction::Reset()
{
	m_IDAssigned=false;
	allocatedByte.clear();
}
