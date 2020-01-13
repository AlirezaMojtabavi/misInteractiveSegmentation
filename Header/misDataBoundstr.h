#pragma once
struct misDataBoundStr
{
	double xMin;
	double xMax;
	double yMin;
	double yMax;
	double zMin;
	double zMax;

	misDataBoundStr()
	{
		xMin = -1;
		xMax = -1;
		yMin = -1;
		yMax = -1;
		zMin = -1;
		zMax = -1;
	}
	void GetArrayBound(double* pBound)
	{
		pBound[0] = xMin;
		pBound[1] = xMax;
		pBound[2] = yMin;
		pBound[3] = yMax;
		pBound[4] = zMin;
		pBound[5] = zMax;
	}

	void SetArrayBound(double pBound[6])
	{
		xMin = pBound[0];
		xMax = pBound[1];
		yMin = pBound[2];
		yMax = pBound[3];
		zMin = pBound[4];
		zMax = pBound[5];
	}
	void ResetToZeroBase()
	{
		xMax =xMax - xMin;
		xMin = 0;
		yMax = yMax - yMin;
		yMin = 0;
		zMax = zMax - zMin;
		zMin = 0;

	}
};