#include "stdafx.h"
#include "misImageCallback.h"

misImageCallback* misImageCallback::New()
{
	return new misImageCallback;
}

misImageCallback::misImageCallback()
{
	m_Scaling = 8.5;
	m_size[0]=512;
	m_size[1]=512;
	m_IsContrastInteractionActive = true;	
}

std::shared_ptr<I2DRepresetation> misImageCallback::GetImageRep() const
{
	return m_pImageRep.lock();
}

void misImageCallback::SetImageRep(std::shared_ptr<I2DRepresetation> val)
{
	m_pImageRep = val; 
}


void misImageCallback::SetSize(int* size)
{
	m_size[0]=size[0];
	m_size[1]=size[1];
	UpdateScaling();
}


void misImageCallback::Execute(vtkObject *caller,unsigned long event,void *vtkNotUsed(calu8lData))
{
	if (event == vtkCommand::ResetWindowLevelEvent)
		m_CurrentLevelWindow = m_InitialLevelWindow;

	if(event==vtkCommand::WindowLevelEvent)
	{
		vtkInteractorStyleImage *interaction = 	dynamic_cast<vtkInteractorStyleImage *>(caller);
		UpdateCurrentWindowLevel(interaction);
	}
	auto imageRep = m_pImageRep.lock();
	if (imageRep)
		imageRep->SetWindowLevel(m_CurrentLevelWindow);

}

void misImageCallback::UpdateCurrentWindowLevel(vtkInteractorStyleImage *interaction)
{

	m_CurrentLevelWindow = m_InitialLevelWindow;

	double window = m_CurrentLevelWindow.GetWindowWidth();
	double level  = m_CurrentLevelWindow.GetWindowCenter();

	// Compute normalized delta
	int xStartPosition = interaction->GetWindowLevelStartPosition()[0];
	int xCurrentPosition=interaction->GetWindowLevelCurrentPosition()[0];

	int yStartPosition = interaction->GetWindowLevelStartPosition()[1];
	int yCurrentPosition=interaction->GetWindowLevelCurrentPosition()[1];

	double dx = m_Scaling * (xStartPosition - xCurrentPosition) / m_size[0];
	double dy = m_Scaling * (yStartPosition - yCurrentPosition) / m_size[1];
	//Scale by current values
 	std::cout << "x:" << xCurrentPosition <<" y :" << yCurrentPosition << std::endl; 

	double minValueChange = 4;

	dx = dx * window;
	dy = dy * level;

	if (fabs(dx) < minValueChange)
	{
		dx = sign(dx);
		dx = dx * minValueChange;
	}
	else if (fabs(dx) < (5 * window / 100))
	{
		dx = sign(dx);
		dx = dx * (5 *window / 100);
	}

	if (fabs(dy) < minValueChange)
	{
		dy = sign(dy);
		dy = dy * minValueChange;
	}
	else if (fabs(dy) < (5* level / 100))
	{
		dy = sign(dy);
		dy = dy * (5*level / 100);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	// Abs so that direction does not flip
	if (window < 0.0) 
	{
		dx = -1*dx;
	}
	if (level < 0.0) 
	{
		dy = -1*dy;
	}

	// Compute new window level

	double newWindow = dx + window;
	double newLevel  = dy + level;

	m_CurrentLevelWindow.SetWindowParams(newLevel, newWindow);
}

void misImageCallback::SetCurrentWindowLevel( misWindowLevelStr winLevStr )
{
	m_CurrentLevelWindow = winLevStr;
}

void misImageCallback::SetDefaultWindowLevel( misWindowLevelStr levWin  )
{
	m_InitialLevelWindow = levWin;
	m_CurrentLevelWindow = m_InitialLevelWindow;
}

void misImageCallback::UpdateScaling( void )
{
	int minSize = m_size[0];
	if (m_size[1] < minSize)
		minSize = m_size[1];
	// Note : 5500 achieved by try and error
	if(minSize == 0)
		m_Scaling = 7;
	else
		m_Scaling = 5500 / minSize;
	if (m_Scaling < 7)
		m_Scaling = 7;
	else if (m_Scaling > 15)
		m_Scaling = 15;
}




void misImageCallback::SetContrastInteraction( bool cntr )
{
	m_IsContrastInteractionActive = cntr;
}

bool misImageCallback::GetContrastInteraction()
{
	return m_IsContrastInteractionActive;
}
