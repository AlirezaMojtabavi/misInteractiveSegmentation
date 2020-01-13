#include "StdAfx.h"
#include "misFpsCalculator.h"

misFpsCalculator::misFpsCalculator(void)
	:averagrFrameRate (25),
	m_timer(vtkSmartPointer<vtkTimerLog>::New())
{
	
}

 

void misFpsCalculator::Start()
{
			m_timer->StartTimer();
 }

void misFpsCalculator::End()
{

	m_timer->StopTimer();
	double elabsed = m_timer->GetElapsedTime();

	double fpsMoment;
	if (elabsed!=0)
		fpsMoment=  1.0/float(elabsed+.0000000001);
	else
		fpsMoment=  1.0/float(0.0001+.0000000001);




	double fps = ( fpsMoment + (59 * this->averagrFrameRate)) /60 ;
	this->averagrFrameRate = fps;

	if ( this->averagrFrameRate > 500)
		this->averagrFrameRate = 100;


	if ( this->averagrFrameRate < 0)
		this->averagrFrameRate = 1;

	


}

 

int misFpsCalculator::GetFps()
{
 return averagrFrameRate;
}
