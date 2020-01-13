#pragma once

#include "misLandmarkenums.h"
#include "misRegistrationEnums.h"
#include "mislandMarkPosAndStatusStr.h"

struct misPairLandMarkStatusStr
{
	LandmarkStatus     m_StatusLandmarkInFixedImage;
	LandmarkStatus     m_StatusMovableLandmark;
	double             m_Error;
};

typedef std::vector<misPairLandMarkStatusStr> misPairLandMarkStatusListType;


/////////////////////////////////////////
struct misPairLandMarkStr
{
private:
	double             m_PositionInFixedImage[3];
	double             m_PositionMovableLandmark[3]; // it comes from from capturing point or select in the second Image
	LandmarkStatus     m_StatusLandmarkInFixedImage;
	LandmarkStatus     m_StatusMovableLandmark;


public:
	misLandmarkType    m_FixedImageLandmarkType; // used for landmark based registration
	double    m_PositionMovableLandmarkAfterRegistration[3];
	double    m_Error;
	int       m_AttemptForCaturing;

	////////////////////////////////////////////////
	misPairLandMarkStatusStr GetPairLandmarkStatus(void)
	{
		misPairLandMarkStatusStr statuses;
		statuses.m_StatusLandmarkInFixedImage = m_StatusLandmarkInFixedImage;
		statuses.m_StatusMovableLandmark      = m_StatusMovableLandmark;
		statuses.m_Error                      = m_Error;
		return statuses;
	}

	double GetError(void)
	{
		return m_Error;
	}

	void ResetRegistrationEffect();;

	double* GetMovablePositionAfterRegistration(void);



	mislandMarkPosAndStatusStr GetFixedLandmarkData()
	{
		 mislandMarkPosAndStatusStr landData;
		 landData.position[0] = m_PositionInFixedImage[0];
		 landData.position[1] = m_PositionInFixedImage[1];
		 landData.position[2] = m_PositionInFixedImage[2];
		 landData.status      = m_StatusLandmarkInFixedImage;
		 landData.error       = m_Error;

		 return landData;
	}

	LandmarkStatus GetFixedLandmarkStatus(void)
	{
		return m_StatusLandmarkInFixedImage;
	}
	void SetFixedLandmark(double position[3])
	{
		m_PositionInFixedImage[0] = position[0];
		m_PositionInFixedImage[1] = position[1];
		m_PositionInFixedImage[2] = position[2];

		m_StatusLandmarkInFixedImage = ValidPoint;
		this->ResetRegistrationEffect();
	};

	double* GetFixedLandmark(void)
	{
		double* position = 0;
		if (ValidPoint == m_StatusLandmarkInFixedImage)
		{
			position = new double[3]; 
			position[0] = m_PositionInFixedImage[0];
			position[1] = m_PositionInFixedImage[1];
			position[2] = m_PositionInFixedImage[2];
		}
        return position;
	};

	void ResetFixedLandmark()
	{
		m_PositionInFixedImage[0] = -1;
		m_PositionInFixedImage[1] = -1;
		m_PositionInFixedImage[2] = -1;
		m_StatusLandmarkInFixedImage = InvalidPoint;

		m_AttemptForCaturing = 0;
		this->ResetRegistrationEffect();
	};
////////////////////////

	mislandMarkPosAndStatusStr GetMovableLandmarkData()
	{
		mislandMarkPosAndStatusStr landData;
		landData.position[0] = m_PositionMovableLandmark[0];
		landData.position[1] = m_PositionMovableLandmark[1];
		landData.position[2] = m_PositionMovableLandmark[2];
		landData.status      = m_StatusMovableLandmark;
		landData.error       = m_Error;
		landData.m_LastView	 = false;

		return landData;
	}

	LandmarkStatus GetMovableLandmarkStatus(void)
	{
		return m_StatusMovableLandmark;
	}

	void SetMovableLandmark(double position[3])
	{
		m_PositionMovableLandmark[0] = position[0];
		m_PositionMovableLandmark[1] = position[1];
		m_PositionMovableLandmark[2] = position[2];

		m_StatusMovableLandmark = ValidPoint;
		this->ResetRegistrationEffect();
	};

	double* GetMovableLandmark(void)
	{
		double* position = 0;
// 		position = this->GetMovablePositionAfterRegistration();
// 		if (!position)
		{
			if (ValidPoint == m_StatusMovableLandmark)
			{
				position = new double[3]; 
				position[0] = m_PositionMovableLandmark[0];
				position[1] = m_PositionMovableLandmark[1];
				position[2] = m_PositionMovableLandmark[2];
			}
		}

		return position;
	};

	void ResetMovableLandmark(void)
	{
		m_PositionMovableLandmark[0] = -1;
		m_PositionMovableLandmark[1] = -1;
		m_PositionMovableLandmark[2] = -1;
		m_StatusMovableLandmark = InvalidPoint;

		this->ResetRegistrationEffect();
	}
	void InactiveMovableLandmark(void)
	{
		this->ResetMovableLandmark();
		m_StatusMovableLandmark = InactivePoint;
	}
////////////////////////////////////////////
	void Reset(void)
	{
       this->ResetFixedLandmark();
	   this->ResetMovableLandmark();

	   this->m_FixedImageLandmarkType = UnkownLandmarkType;
	};

	misPairLandMarkStr()
	{
      this->Reset();
	};
};

typedef std::vector<misPairLandMarkStr> misPairLandMarkListType;
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
