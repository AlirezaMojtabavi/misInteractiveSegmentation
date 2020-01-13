#include "stdafx.h"
#include "misStrct3DLayer.h"

misOpenglTexture* misStrct3DLayer::GetTexure() const
{

	return m_pTexure;
}

void misStrct3DLayer::SetTexure(misOpenglTexture* val)
{

	m_pTexure = val;
}

misStrct3DLayer::misStrct3DLayer()
{
	m_pTexure = NULL;
}
