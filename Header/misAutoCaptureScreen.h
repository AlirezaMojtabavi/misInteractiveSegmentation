#pragma once

#include "misAutoCaptureScreenStrcts.h"
#include "misMacros.h"
#include "misTrackedToolEnums.h"

class misAutoCaptureScreen
{
	vtkTimerLog*               m_Timer;
	misCaptureScreenStatus     m_LastCaptureScreenStatus;
	double                     m_ElapsedTime;

public:
	misAutoCaptureScreen(void);
	~misAutoCaptureScreen(void);

	misCreateVariableWithSetGetMacro(DelayTimeForStart,double);
	misCreateVariableWithSetGetMacro(DelayTimeToPause, double);
	misCreateVariableWithSetGetMacro(DelayTimeToStop, double);
	misCreateVariableWithGetMacro(AutoRecCaptureStatus,bool);
	misCreateVariableWithGetMacro(ExternalActivation,bool);

	void Reset(void);
	void SetAutoRecCaptureStatus(bool val);

	void SetExternalActivation(misCaptureScreenStatus userRequestCaptureScreenStatus);
	void SetToolStatus(bool toolIsReady);
	misCaptureScreenStatus GetActionStatus(void);


private:
	void StartCapturing(void);
	void TryToStartCapturing(void);
	void TryToPauseCapturing(void);
	void TryToStopCapturing(void);
	bool ChangeStatusOnElapsedTime(double validTime);
};

