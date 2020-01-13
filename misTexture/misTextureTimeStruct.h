#pragma once

class misOpenglTexture;
struct misTextureTimeStruct
{
public:

	vtkTimeStamp pLoadTime;
	misOpenglTexture* pLoadTexture; 
	misTextureTimeStruct(void);
	~misTextureTimeStruct(void);
};

