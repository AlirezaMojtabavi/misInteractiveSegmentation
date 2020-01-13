#include "StdAfx.h"
#include "misImageDataProperties.h"


misImageDataProperties::misImageDataProperties(void)
{
}

void misImageDataProperties::DeepCopy( misImageDataProperties* T )
{
	imagingProprties    = T->imagingProprties;
	patientProperties   = T->patientProperties;
	hardwareProperties  = T->hardwareProperties;
	imageProperties     = T->imageProperties;
	serieProperties     = T->serieProperties;
	studyProperties     = T->studyProperties;
	m_ViewingProperties   = T->m_ViewingProperties;
}

void misImageDataProperties::SetWindowParams( double center, double width )
{
	misWindowLevelStr winLev;
	winLev.SetWindowParams(center, width);
	m_ViewingProperties.SetLevelWindow(winLev);
}

void misImageDataProperties::SetDefaultThresholdForSkinViewing( double val )
{
	m_ViewingProperties.SetDefaultThresholdForSkinViewing(val);
}

void misImageDataProperties::SetDefaultThresholdForBoneViewing(double val)
{
	m_ViewingProperties.SetDefaultThresholdForBoneViewing(val);
}
 

boost::optional<double> misImageDataProperties::GetCurrentThresholdForSkinViewing() const
{
		return m_ViewingProperties.GetCurrentThresholdForSkinViewing();
}

void misImageDataProperties::SetCurrentThresholdForSkinViewing( double val )
{
	m_ViewingProperties.SetCurrentThresholdForSkinViewing(val);
}

boost::optional<double> misImageDataProperties::GetDefaultThresholdForSkinViewing() const
{
	return m_ViewingProperties.GetDefaultThresholdForSkinViewing();
}

boost::optional<double> misImageDataProperties::GetDefaultThresholdForBoneViewing() const
{
	return m_ViewingProperties.GetDefaultThresholdForBoneViewing();
}

misImageViewingType misImageDataProperties::GetViewingNameType() const
{
	return m_ViewingProperties.GetViewingNameType();
}

void misImageDataProperties::SetViewingNameType( misImageViewingType val )
{
	m_ViewingProperties.SetViewingNameType(val);
}

misWindowLevelStr misImageDataProperties::GetWindowlevel() const
{
	return m_ViewingProperties.GetLevelWindow();
}

void misImageDataProperties::SetWindowlevel( misWindowLevelStr val )
{
	m_ViewingProperties.SetLevelWindow(val);
}

boost::optional<double> misImageDataProperties::GetCurrentThresholdForBoneViewing() const
{
	return m_ViewingProperties.GetCurrentThresholdForBoneViewing();
}

void misImageDataProperties::SetCurrentThresholdForBoneViewing( double val )
{
	m_ViewingProperties.SetCurrentThresholdForBoneViewing(val);
}

boost::optional<double> misImageDataProperties::GetCurrentThresholdForTeethViewing() const
{
	return m_ViewingProperties.GetCurrentThresholdForTeethViewing();
}

void misImageDataProperties::SetCurrentThresholdForTeethViewing( double val )
{
	m_ViewingProperties.SetCurrentThresholdForTeethViewing(val);
}

ImageColorTableType misImageDataProperties::GetColorMapType() const
{
	return m_ViewingProperties.GetColorMapType();
}

void misImageDataProperties::SetColorMapType( ImageColorTableType val )
{
	m_ViewingProperties.SetColorMapType(val);
}

misImageViewingProperties misImageDataProperties::GetViewingProperties() const
{
	return m_ViewingProperties;
}

void misImageDataProperties::SetViewingProperties( misImageViewingProperties val )
{
	m_ViewingProperties = val;
}

