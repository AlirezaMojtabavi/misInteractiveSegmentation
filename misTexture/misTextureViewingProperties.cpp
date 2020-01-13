#include "stdafx.h"
#include "misTextureViewingProperties.h"

misTextureViewingProperties::misTextureViewingProperties()
	: CurrentWindowCenterOfMT(0.4), CurrentWindowWidthOfMT(0.8), UseAlphaForMainBlending(true), UseColorForMT(true), 
	VisiblityofSegmentedImage(false), VisiblityOfColorMap(false), MainImageID(-1), m_SegmentedImageID(-1), 
	 FmriImageTransferFuncID(-1), m_ColorMap(nullptr), VisiblityofFmriImage(false), m_OpacityOfMT(1.0), 
	m_VisiblityOfMT(true), m_fMRIID(-1), m_WindowLevelTransferFuncID(-1), mainImageIsColored(false)
{
}

void misTextureViewingProperties::SetVisiblityofFmriImage( bool visible )
{
	this->VisiblityofFmriImage = visible;
}

bool misTextureViewingProperties::GetVisiblityofFmriImage()const
{
	return VisiblityofFmriImage;
}

float misTextureViewingProperties::GetOpacityOfMT() const
{
	return m_OpacityOfMT;
}

void misTextureViewingProperties::SetOpacityOfMT( float val )
{
	m_OpacityOfMT = val;
}

bool misTextureViewingProperties::GetVisiblityOfMT() const
{
	return m_VisiblityOfMT;
}

void misTextureViewingProperties::SetVisiblityOfMT( bool val )
{
	m_VisiblityOfMT = val;
}

void misTextureViewingProperties::SetfMRIImageID( int fMRIID )
{
	m_fMRIID = fMRIID;
}

int misTextureViewingProperties::GetfMRIImageID()
{
	return m_fMRIID;
}

bool misTextureViewingProperties::GetMainImageIsColored() const
{
	return mainImageIsColored;
}

void misTextureViewingProperties::SetMainImageIsColored( bool val )
{
	mainImageIsColored = val;
}

int misTextureViewingProperties::GetSegmentedImageID() const
{
	return m_SegmentedImageID;
}

void misTextureViewingProperties::SetSegmentedImageID(int val)
{
	m_SegmentedImageID = val;
}

void misTextureViewingProperties::SetColorValueOfMainTexture(const misDoubleColorStruct& color)
{
	m_ColorValueOfMainTexture = color;
}

misDoubleColorStruct misTextureViewingProperties::GetColorValueOfMainTexture() const
{
	return m_ColorValueOfMainTexture;
}

int misTextureViewingProperties::GetWindowLevelTransferFuncID() const
{
	return m_WindowLevelTransferFuncID;
}


void misTextureViewingProperties::SetWindowLevelTransferFuncID( int textureId )
{
	if (m_WindowLevelTransferFuncID > 0 &&
		m_WindowLevelTransferFuncID != textureId)
	{
		if (glIsTexture(m_WindowLevelTransferFuncID))
		{
			GLuint texureID = m_WindowLevelTransferFuncID;
			glDeleteTextures(1, (const GLuint*)&texureID);
		}
	}
	m_WindowLevelTransferFuncID = textureId;
}

std::shared_ptr<TransFuncIntensity> misTextureViewingProperties::GetColorMap() const
{
	return m_ColorMap;
}

void misTextureViewingProperties::SetColorMap(std::shared_ptr<TransFuncIntensity> val)
{
	m_ColorMap = val;
}

bool misTextureViewingProperties::GetVisiblityOfColorMap() const
{
	return VisiblityOfColorMap;
}

void misTextureViewingProperties::SetVisiblityOfColorMap(bool val)
{
	VisiblityOfColorMap = val;
}

bool misTextureViewingProperties::GetVisiblityofSegmentedImage() const
{
	return VisiblityofSegmentedImage;
}

void misTextureViewingProperties::SetVisiblityofSegmentedImage(bool val)
{
	VisiblityofSegmentedImage = val;
}

std::shared_ptr<TransFuncIntensity> misTextureViewingProperties::GetSegmentedImageTransferFunc() const
{
	return m_SegmentedImageTransferFunc;
}

void misTextureViewingProperties::SetSegmentedImageTransferFunc(std::shared_ptr<TransFuncIntensity> val)
{
	m_SegmentedImageTransferFunc = val;
}
