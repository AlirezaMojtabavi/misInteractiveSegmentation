#pragma once

#include "misGuiStructures.h"
#include "misSTRCT.h"
#include "mislandMarkPosAndStatusStr.h"
#include "Point.h"

class misCalculateDistance
{
public:

	misCalculateDistance(void);
	virtual ~misCalculateDistance(void);

	virtual void Reset(void);
	void SetActivationState(bool state);
	bool GetActivationState(void);
	LandmarkStateListTypdef   GetState(void);
	void GetPosition(int index, double position[3]);
	int GetNumberOfActiveLandmarks();

	virtual bool SetLandmarkPosition(parcast::PointD3 pos);
	virtual void ChangeButtonState(int buttonNumber);
	virtual double GetDistance(void);
protected:
	bool m_Activation;
	std::vector<mislandMarkPosAndStatusStr> m_ButtonS;
	double m_Distance;
	LandmarkStateListTypdef m_LandmarksState;
private:	
	void UpdateGUIState(void);

};

