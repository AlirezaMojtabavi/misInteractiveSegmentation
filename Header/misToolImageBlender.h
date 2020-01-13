#pragma   once

#include "misExtraToolInformation.h"
#include "misToolImageStrct.h"

namespace  Gdiplus
{
	class Bitmap;
};

class  misToolImageBlneder
{
public:
	misToolImageBlneder();
	~misToolImageBlneder();

	void    SetMainImage( std::shared_ptr<Gdiplus::Image> mainImage );
	void    SetMarkerImages(std::vector<std::shared_ptr<Gdiplus::Image>> markerImageList);
	HBITMAP GetBlendedImageHandle(misExtraToolInformation extraToolInformation);

	void   ResetImages(void);

private:
    misToolImageStrct       m_ToolImages;
	Gdiplus::Image*         m_ResultImage;

	//AHK : Note : This Method added for further use in bitmap saving as a test and should be deleted .
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	HBITMAP  m_hBitmap ;
};