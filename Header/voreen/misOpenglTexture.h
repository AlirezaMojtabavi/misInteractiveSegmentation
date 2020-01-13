#pragma once
#include "tgt/texture.h"
#include "misTexturePropertyStruct.h"
#include "misWindowLevelStr.h"
#include "misROI.h"

# define TYPE_CAST(T, V) static_cast< T >(V)
#define UNSIGNED_CHAR_MAX       TYPE_CAST(unsigned char, 0xffu)
#define SIGNED_CHAR_MAX         TYPE_CAST(signed char, 0x7f)
#define SHORT_MAX               TYPE_CAST(short, 0x7fff)
#define UNSIGNED_SHORT_MAX      TYPE_CAST(unsigned short, 0xffffu)
#define UNSIGNED_INT_MAX        TYPE_CAST(unsigned int, ~0u)

class TGTLIBMISDLLEXPORT misOpenglTexture : public tgt::Texture
{
public:

	misOpenglTexture(misTexturePropertyStruct textureProp, tgt::Texture::Filter filter);
	~misOpenglTexture(void);
	misTexturePropertyStruct	GetTexturePropertyStrct() { return m_TexPropStrct; };
	double*						GetTableRange() { return m_TableRange; }
	std::string	GetImageUID() const;
	void SetImageUID(std::string uId);
	void SetWindowLevel(misWindowLevelStr WinLevStr);
	misWindowLevelStr	GetWindowLevel();
	std::string GetParentimageID() const;
	void SetParentimageID(std::string val);
	void ReleaseTextureResource();
	bool	GetIsPolydataFlag();
	void	SetIsPolydataFlag(bool val);
	void	SetROI(misROI roi);
	misROI	GetROI();

private:

	void CalculateBias(GLenum dataType);
	void SetTableRange(double* tableRange);
	misTexturePropertyStruct	m_TexPropStrct;
	double m_shift;
	double*	m_TableRange;
	double m_scale;
	bool m_IsPolydata;
	std::string	m_imageID;
	std::string	m_ParentimageID;
};

