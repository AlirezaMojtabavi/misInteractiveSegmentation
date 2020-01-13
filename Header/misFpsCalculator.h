#pragma once
class vtkTimerLog;
class misFpsCalculator
{
public:
	void Start();
	void End();
	int GetFps();
	misFpsCalculator(void);

private:
	vtkSmartPointer<vtkTimerLog> m_timer;
	double  averagrFrameRate;


};
