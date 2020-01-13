#pragma once

#ifndef misColorImage_H
#define misColorImage_H

#include "misColorTable.h"
#include "misImage.h"
#include "misSeconderyNeededHeader.h"

#define  ImageContainedDataType unsigned short //2Byte output
/*#define  ImageContainedDataType unsigned char   //1Byte output*/

class  misColorImage
{
	misCreateVariableWithSetGetMacro(DefaultColor,misColorStruct);

private:

	vtkImageData*					 m_InImage;
	unsigned short*					 m_InImageDataPointer;
	int*							 m_ImageDimentions;
	misColorListTypedef              m_ColorTable;
	misColorStruct*                  m_ColorArray;
	int                              m_ArraySize ;
	misColorListTypedef::iterator    m_ColorIter;
	bool                             m_UpdatedOutput;
	vtkImageData*                    m_OutImage;
	unsigned char*                   m_OutImageDataPointer;
	int                              m_InputType;

private:
	misResultCode::ResultIds	InitializeOutImage(void);
	misResultCode::ResultIds	CheckOutImageProperties(void);
	misResultCode::ResultIds	ComputeOutImage(void);
	//	void                        FillColorArray(void);
	inline void  FillByColor( misColorStruct  color );


public:
	static misColorImage* New(void)
	{
		return new misColorImage;
	};

	misResultCode::ResultIds    SetInputImage                 (vtkImageData*       pImage);
	misResultCode::ResultIds    SetInputImageUnsignedShortType(vtkImageData*       pImage);

	//void                        SetColorTable(misColorListTypedef colorTable);
	void                        SetColorTable(misColorStruct* colorStr256256);

	void                        clear(void);

	vtkImageData*   GetOutput(void);

	misColorImage(void);
	~misColorImage(void);



};
#endif
