#include "stdafx.h"
#include "misStrctLayer.h"

#include "misOpenglTexture.h"

misStrctLayer::misStrctLayer()
{
 
	m_pSource=NULL;
	m_GrayScaleMapping=true;
}

void misStrctLayer::SetSource( std::shared_ptr<IImage> val )
{
	m_pSource = val;
	//m_pSource->Register()
}

std::shared_ptr<IImage> misStrctLayer::GetSource() const
{
	return m_pSource;
}

void misStrctLayer::Enable()  
{
	m_Enable=true;
}

void misStrctLayer::Disable()
{
	m_Enable = false;
}

bool misStrctLayer::IsEnabled()  const
{
	return m_Enable;
}

void misStrctLayer::GrayScaleMappingOff()
{
	this->m_GrayScaleMapping=false;

}

void misStrctLayer::GrayScaleMappingOn()
{
	this->m_GrayScaleMapping=true;

}
 

misWindowLevelStr misStrctLayer::GetWinlevel() const
{
	return m_Winlevel;
}

void misStrctLayer::SetWinlevel(misWindowLevelStr val)
{
	m_Winlevel = val;
}

//misRootVolumeTexture* misStrct3DLayer::GetTexure() const
//{
//
//	return m_pTexure;
//}