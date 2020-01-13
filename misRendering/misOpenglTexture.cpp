#include "StdAfx.h"
#include "misOpenglTexture.h"
#include <iosfwd>
#include "misWindowLevelStr.h"

using std::stringstream;

misOpenglTexture::misOpenglTexture(misTexturePropertyStruct textureProp,tgt::Texture::Filter filter):
Texture((GLubyte*)textureProp.Data,textureProp.GetDimensions(), textureProp.Format, textureProp.InternalFormat, 
	textureProp.DataType,filter,false)

{
	m_TexPropStrct = textureProp;
	m_TexPropStrct.Filter = filter ;
	if (filter == NEAREST)
		SetIsPolydataFlag(true);
	else
		SetIsPolydataFlag(false);
	SetTableRange(textureProp.GetTableRange());
	CalculateBias(textureProp.DataType);
	setWrapping(tgt::Texture::Wrapping::CLAMP_TO_BORDER);
	uploadTexture(m_shift,m_scale);
	glBindTexture(GL_TEXTURE_3D,0);
	GLboolean  validation= glIsTexture(this->id_);
	_ASSERT(validation == GL_TRUE);

}

misOpenglTexture::~misOpenglTexture(void)
{
}

void misOpenglTexture::CalculateBias(GLenum dataType)
{
	_ASSERT(m_TableRange[1] != m_TableRange[0]);

	double shift,scale;

	switch(dataType)
	{
	case GL_FLOAT:
		shift=-m_TableRange[0];
		scale=1/(m_TableRange[1]-m_TableRange[0]);
		break;
	case GL_UNSIGNED_BYTE:
		shift = 0;
		scale = 1;
		break;
	case GL_BYTE:
		shift = 0;
		scale = 1;
		break;
	case GL_3_BYTES:
		shift = 0;
		scale = 1;
		break;
	case GL_SHORT:
		shift = -(2*m_TableRange[0]+ 1)/ UNSIGNED_SHORT_MAX;
		scale = SHORT_MAX / (m_TableRange[1] - m_TableRange[0]) ;
		break;
	case GL_UNSIGNED_SHORT:
		shift = -m_TableRange[0]/ UNSIGNED_SHORT_MAX;
		scale = UNSIGNED_SHORT_MAX / (m_TableRange[1] - m_TableRange[0]) ;
		break;
	case GL_INT:
		shift=-(2*m_TableRange[0]+1)/ UNSIGNED_INT_MAX;
		scale = INT_MAX/(m_TableRange[1]-m_TableRange[0]);
		break;
	case GL_UNSIGNED_INT:
		shift=-m_TableRange[0]/ UNSIGNED_INT_MAX;
		scale= UNSIGNED_INT_MAX/(m_TableRange[1] - m_TableRange[0]);
		break;
	default:
		_ASSERT(true==false);
		break;
	}

	m_scale = scale;
	m_shift = shift;
	//m_scale = 1;
	//m_shift = 0;
}

bool misOpenglTexture::GetIsPolydataFlag()
{
	return m_IsPolydata;
}

void misOpenglTexture::SetIsPolydataFlag( bool val )
{
	this->m_IsPolydata = val;
}

void misOpenglTexture::SetTableRange( double* tableRange )
{
	m_TableRange = new double[2];
	m_TableRange[0] = tableRange[0];
	m_TableRange[1] = tableRange[1];

}

void misOpenglTexture::ReleaseTextureResource()
{
	GLuint tempIndex;
	tempIndex = getId();
	glDisable(type_);
	glDeleteTextures(1, &tempIndex);
}

void misOpenglTexture::SetImageUID( std::string uId )
{
	this->m_imageID = uId;
}
std::string misOpenglTexture::GetImageUID() const
{
	return this->m_imageID;
}

void misOpenglTexture::SetWindowLevel( misWindowLevelStr WinLevStr )
{
	m_TexPropStrct.SetWindowLevel(WinLevStr.GetWindowWidth());
	m_TexPropStrct.SetWindowCenter(WinLevStr.GetWindowCenter());
}

misWindowLevelStr misOpenglTexture::GetWindowLevel()
{
	misWindowLevelStr levelCenter;
	levelCenter.SetWindowParams(m_TexPropStrct.GetWindowCenter(), m_TexPropStrct.GetWindowLevel());
	return  levelCenter;
}

std::string misOpenglTexture::GetParentimageID() const
{
	return m_ParentimageID;
}

void misOpenglTexture::SetParentimageID( std::string val )
{
	m_ParentimageID = val;
}

void misOpenglTexture::SetROI( misROI roi )
{
	m_TexPropStrct.SetROI(roi);
}

misROI misOpenglTexture::GetROI()
{
	return  m_TexPropStrct.GetROI();
}

 

