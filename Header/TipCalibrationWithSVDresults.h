//This header is written by -M.A- for handling results of SVD 6 point tip calibration 
#pragma once

#include "misTrackingManagerEnums.h"

struct SVDTipCalibrationResults
{
public:
	//calculated offset with svd
	double Offset[3];

	//calculated Pivot with svd approach
	double Pivot[3];

	double RMSE;
	double MaxError;
	double MeanError;

	//stores svd.sigma_max();
	double MaxValueOfSVD;

	//stores svd.sigma_min();
	double MinValueOfSVD;

	double NumericQualityOfSpheresOfNDI;

	//initializes all structure members with -1
	SVDTipCalibrationResults()
	{
		Reset();
	};

	//determines whether the tool tip during data Gathering process was fixed or not
	//true means fixed tool tip, false means moving tool tip
	bool IsToolTipFix()
	{
		if(MaxError > 3)
		{
			return false;
		}
		return true;
	};

	//determines if the quality of gathered data is good or not
	//true means data is good, false means bad data
	bool DataIsQualified()
	{
		double Sparcity=(MaxValueOfSVD/MinValueOfSVD);
		if(Sparcity < 20)
		{
			return true;
		}
		return false;
	};

	//returns the quality of spheres of NDI
	NDItoolSpheresQuality NDIspheresQuality()
	{
		NDItoolSpheresQuality QualityResult = Inappropriate;

		if(NumericQualityOfSpheresOfNDI < 50)
		{
			QualityResult = Inappropriate;
		}
		else if((50 <= NumericQualityOfSpheresOfNDI) && (NumericQualityOfSpheresOfNDI <= 175))
		{
			QualityResult = Acceptable;
		}
		else if(175 < NumericQualityOfSpheresOfNDI)
		{
			QualityResult = VeryGood;
		}
		return QualityResult;
	};
	void Reset()
	{
		for(int i=0;i<3;i++)
		{
			Offset[i]=-1.0;
			Pivot[i]=-1.0;
		}
		RMSE=-1.0;
		MaxError=-1.0;
		MeanError=-1.0;
		MaxValueOfSVD=-1.0;
		MinValueOfSVD=-1.0;
		NumericQualityOfSpheresOfNDI=-1.0;
	};


};