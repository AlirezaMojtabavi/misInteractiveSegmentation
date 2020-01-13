#ifndef misStrctColorData_H
#define misStrctColorData_H

#include "misColorStruct.h"
#include "misImageModalityEnum.h"
	
// range between 0:1
struct misDoubleColorStruct
{
	double Red;
	double Green;
	double Blue;
	double Alpha;

	misDoubleColorStruct(double r, double g, double b, double a)
		: Red(r),
		  Green(g),
		  Blue(b),
		  Alpha(a)
	{
	}

	misDoubleColorStruct(void)
	{
		Red = 0.5;
		Green = 0.5;
		Blue = 0.5;
		Alpha = 1;
	};

	void SetColorToRed(void)
	{
		Red = 242.0 / 255.0;
		Green = 15.0 / 255.0;
		Blue = 15.0 / 255.0;
	}

	void SetColorToGreen(void)
	{
		Red = 42.0 / 255.0;
		Green = 212.0 / 255.0;
		Blue = 93.0 / 255.0;
	}

	void SetColorToYellow(void)
	{
		Red = 255.0 / 255.0;
		Green = 255.0 / 255.0;
		Blue = 0.0 / 255.0;
	}

	void SetColorToBlue(void)
	{
		Red = 42.0 / 255.0;
		Green = 139.0 / 255.0;
		Blue = 255.0 / 255.0;
	}

	void InVisible(void)
	{
		Red = 0;
		Green = 0;
		Blue = 0;

		Alpha = 0;
	};


	bool operator ==(const misDoubleColorStruct right)
	{
		if ((this->Red == right.Red) && (this->Green == right.Green) && (this->Blue == right.Blue) && (this->Alpha ==
			right.Alpha))
			return true;
		else
			return false;
	};


	bool operator !=(misDoubleColorStruct right)
	{
		bool res = !(*this == right);
		return res;
	};
};

typedef std::map<double, misDoubleColorStruct> misDoubleColorListTypedef;

struct VolumeColorMapStrct
{
	std::string Name;
	misImageDataModality ImageModality;
	misColorStruct Colormap;

	VolumeColorMapStrct()
	{
		ImageModality = NoData;
	}
};

#endif
