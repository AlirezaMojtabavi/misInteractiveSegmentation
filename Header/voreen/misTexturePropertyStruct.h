#pragma once
#include "misWindowLevelStr.h"
#include "misImageModalityEnum.h"
#include "tgtMacroHeader.h"
#include "misROI.h"

struct misTexturePlanePoint
{
	std::vector<tgt::vec3 >  Points ;
	void SetToZero()
	{
		Points.resize(3);

		for (int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				Points[i][j] = 0;
			}
		}
	}
};

class TGTLIBMISDLLEXPORT  misTexturePropertyStruct
{
public:
	double*  GetRealDimension();//safe to delete return pointer;3 element
	double*  GetRealExtend();//safe to delete return pointer;6 elemnt
	const int* GetExtent();
	void SetExtent(const int* extent);
	tgt::ivec3 GetDimensions();
	void Reset(void);
	misTexturePropertyStruct();
	bool IsValid(void);
	void SetWindowCenter(double value);
	void SetWindowLevel(double value);
	double GetWindowCenter();
	double GetWindowLevel();
	misROI GetROI() const;
	void SetROI(const misROI& val);
	void SetTableRane(double* tableRange);
	double* GetTableRange();

	void*					Data;
	GLint					Format;
	GLint					InternalFormat;
	GLenum					DataType;
	tgt::Texture::Filter	Filter;

	double*					Origin;
	misImageDataModality	Modality;
	tgt::vec3				Spacing;
	int						BitStored;
	int						ScalarType;

private:
	misROI                  m_ROI;
	double					TableRange[2];
	misWindowLevelStr		WindowLevel;
	int						Extent[6];

};

