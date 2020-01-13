#pragma once
#include "misRegistrationEnums.h"

struct TREStrct
{
	int    landmarkIndex;
	double Error;

	void Reset()
	{
		this->landmarkIndex = -1;
		this->Error = -1;
	}

	TREStrct()
	{
		this->Reset();
	}
};

struct RegistrationResultStr
{
	RegistrationResult	regState;
	double errorMean;
	double errorSTD;
	unsigned int NumOfValidLandmarks;
	int worstLandMark;

	void Reset()
	{
		errorMean = -1;
		errorSTD = -1;
		worstLandMark = -1;
		regState = PointSizeError;
	}

	RegistrationResultStr()
	{
		this->Reset();
	}
	bool operator == (RegistrationResultStr& right)
	{
		if (errorMean != right.errorMean)
		{
			return false;
		}
		if (errorSTD != right.errorSTD)
		{
			return false;
		}
		if (worstLandMark != right.worstLandMark)
		{
			return false;
		}
		return true;
	}
};