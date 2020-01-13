#pragma once

#include "misSimplePointType.h"

class misHexFaceObject
{
private:
	struct misfaceData
	{
		misSimplePointType faceCenterPosition;
		misSimplePointType faceNormal;

		void Reset()
		{
			faceCenterPosition.SetPoint(0.0,0.0,0.0);
			faceNormal.SetPoint(0.0,0.0,0.0);
		}

		misfaceData()
		{
			Reset();
		}
	};

	typedef std::vector<misfaceData> FacesDataTypdef;
	FacesDataTypdef             m_Faces;
	double                      m_CubeHeight;
	double                      m_RealPlateCenter[2];
    double                      m_PlateExpanding;
	double                      m_HighLevelExpander;

	bool IsInBeforeSide(misfaceData faceData, double* position);
	void InitialDefautValues(void);
	void InitialFaces(void);

public:
	misHexFaceObject(void);
	~misHexFaceObject(void);

	bool CheckIsInObject(double position[3]);
	

};

