#include "stdafx.h"
#include "mis3DModelViewingProperties.h"

void mis3DModelObjectOpacityPropertiesStrct::Reset()
{
	visibilityIn2DScene = true;
	m_VisibilityIn3DScene = true;
	m_OpacityIn2DScene = 1.0;
	OpacityIn3DScene = 1.0;
}

mis3DModelObjectOpacityPropertiesStrct::mis3DModelObjectOpacityPropertiesStrct(void)
{
	Reset();
}

void mis3DModelObjectOpacityPropertiesStrct::operator=(mis3DModelObjectOpacityPropertiesStrct right)
{
	visibilityIn2DScene = right.visibilityIn2DScene;
	m_VisibilityIn3DScene = right.m_VisibilityIn3DScene;
	m_OpacityIn2DScene = right.GetOpacityIn2DScene();
	OpacityIn3DScene = right.OpacityIn3DScene;
}

bool mis3DModelObjectOpacityPropertiesStrct::operator==(const mis3DModelObjectOpacityPropertiesStrct &right) const
{
	return visibilityIn2DScene == right.visibilityIn2DScene &&
		m_VisibilityIn3DScene == right.m_VisibilityIn3DScene &&
		m_OpacityIn2DScene == right.m_OpacityIn2DScene &&
		OpacityIn3DScene == right.OpacityIn3DScene;
}

bool mis3DModelObjectOpacityPropertiesStrct::operator!=(mis3DModelObjectOpacityPropertiesStrct right) const
{
	return !(*this == right);
}

void mis3DModelObjectOpacityPropertiesStrct::SetAllInvisible()
{
	visibilityIn2DScene = false;
	m_VisibilityIn3DScene = false;
}

void mis3DModelObjectOpacityPropertiesStrct::SetAllVisible()
{
	visibilityIn2DScene = true;
	m_VisibilityIn3DScene = true;
}

double mis3DModelObjectOpacityPropertiesStrct::GetOpacityIn2DScene() const
{
	return m_OpacityIn2DScene;
}

void mis3DModelObjectOpacityPropertiesStrct::SetOpacityIn2DScene(double val)
{
	m_OpacityIn2DScene = val;
}

bool mis3DModelObjectOpacityPropertiesStrct::GetVisibilityIn2DScene() const
{
	return visibilityIn2DScene;
}

bool mis3DModelObjectOpacityPropertiesStrct::GetVisibilityIn3DScene() const
{
	return m_VisibilityIn3DScene;
}

void mis3DModelObjectOpacityPropertiesStrct::SetVisibilityIn3DScene(bool val)
{
	m_VisibilityIn3DScene = val;
}

