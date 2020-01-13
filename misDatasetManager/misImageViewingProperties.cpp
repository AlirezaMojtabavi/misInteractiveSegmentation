#include "StdAfx.h"
#include "misImageViewingProperties.h"


void misImageViewingProperties::Reset( void )
{
 	SetColorMapType(GrayScaleImage);
	m_Windowlevel = m_InitialLevelWindow;

}


boost::optional<double> misImageViewingProperties::GetDefaultThresholdForSkinViewing() const
{
	return m_DefaultThresholdForSkinViewing;
}

boost::optional<double> misImageViewingProperties::GetDefaultThresholdForBoneViewing() const
{
	return m_DefaultThresholdForBoneViewing;
}

void misImageViewingProperties::SetDefaultThresholdForSkinViewing( double val )
{
	m_DefaultThresholdForSkinViewing = val;
}

void misImageViewingProperties::SetDefaultThresholdForBoneViewing(double val)
{
	m_DefaultThresholdForBoneViewing= val;
}

boost::optional<double> misImageViewingProperties::GetCurrentThresholdForSkinViewing() const
{
	return m_CurrentThresholdForSkinViewing;
}

void misImageViewingProperties::SetCurrentThresholdForSkinViewing( double val )
{
	m_CurrentThresholdForSkinViewing = val;
}

boost::optional<double> misImageViewingProperties::GetCurrentThresholdForBoneViewing() const
{
	return m_CurrentThresholdForBoneViewing;
}

void misImageViewingProperties::SetCurrentThresholdForBoneViewing( double val )
{
	m_CurrentThresholdForBoneViewing = val;
}

boost::optional<double> misImageViewingProperties::GetCurrentThresholdForTeethViewing() const
{
	return m_CurrentThresholdForTeethViewing;
}

void misImageViewingProperties::SetCurrentThresholdForTeethViewing( double val )
{
	m_CurrentThresholdForTeethViewing = val;
}

boost::optional<double> misImageViewingProperties::GetCurrentThresholdForSkinFilledViewing() const
{
	return m_CurrentThresholdForSkinFilledViewing;
}

void misImageViewingProperties::SetCurrentThresholdForSkinFilledViewing( double val )
{
	m_CurrentThresholdForSkinFilledViewing = val;
}

misWindowLevelStr misImageViewingProperties::GetLevelWindow() const
{
	return m_Windowlevel;
}

void misImageViewingProperties::SetLevelWindow( misWindowLevelStr val )
{
	m_Windowlevel = val;
}

misImageViewingType misImageViewingProperties::GetViewingNameType() const
{
	return ViewingNameType;
}

void misImageViewingProperties::SetViewingNameType( misImageViewingType val )
{
	ViewingNameType = val;
}

ImageColorTableType misImageViewingProperties::GetColorMapType() const
{
	return ColorMapType;
}

void misImageViewingProperties::SetColorMapType( ImageColorTableType val )
{
	ColorMapType = val;
}

void misImageViewingProperties::SetWindowParams( double center, double width)
{
	m_Windowlevel.SetWindowParams(center, width);
}

misWindowLevelStr misImageViewingProperties::GetInitialLevelWindow() const
{
	return m_InitialLevelWindow;
}

void misImageViewingProperties::SetInitialLevelWindow(misWindowLevelStr val)
{
	m_InitialLevelWindow = val;
}

misImageViewingProperties::misImageViewingProperties()
{
	Reset();
}
