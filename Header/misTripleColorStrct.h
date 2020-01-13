#pragma once
#include "misStrctColorData.h"


enum misTripleColorType
{
	TripleNormal,
	TripleRed,
	TripleWarm,
	TripleUnsetvalue,
};

struct misTripleColorStrct
{
	misDoubleColorStruct XColor;
	misDoubleColorStruct YColor;
	misDoubleColorStruct ZColor;

	void Reset()
	{
		XColor.SetColorToGreen();
		YColor.SetColorToRed();
		ZColor.SetColorToBlue();
	}

	misTripleColorStrct()
	{
		Reset();
	};

	void SetTripleColorType(misTripleColorType tripleColorType)
	{
		switch (tripleColorType)
		{
		case TripleNormal:
			this->Reset();
			break;

		case TripleRed:
			XColor.SetColorToRed();
			YColor.SetColorToRed();
			ZColor.SetColorToRed();
			break;

		case TripleWarm:
			XColor.Red   = 255.0 / 255.0;
			XColor.Green = 0.0 / 255.0;
			XColor.Blue  = 255.0 / 255.0;

			YColor.SetColorToRed();

			ZColor.Red   = 220.0 / 255.0;
			ZColor.Green = 128.0 / 255.0;
			ZColor.Blue  = 0.0 / 255.0;
			break;

		default:
			this->Reset();
		}
	}
};