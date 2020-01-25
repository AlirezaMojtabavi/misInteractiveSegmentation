#include "stdafx.h"
#include "..\Header\WindowLevelSetting.h"

#include "misDebug.h"

parcast::WindowLevelSetting::WindowLevelSetting()
{
	m_Scaling = 8.5;
	m_size[0] = 512;
	m_size[1] = 512;
	m_IsContrastInteractionActive = true;
}

void parcast::WindowLevelSetting::Reset()
{
	m_CurrentLevelWindow = m_InitialLevelWindow;
}

void parcast::WindowLevelSetting::UpdateScaling(void)
{
	int minSize = m_size[0];
	if (m_size[1] < minSize)
		minSize = m_size[1];
	// Note : 5500 achieved by try and error
	if (minSize == 0)
		m_Scaling = 2;
	else
		m_Scaling = 5500 / minSize;
	if (m_Scaling < 1)
		m_Scaling = 1;
	else if (m_Scaling > 4)
		m_Scaling = 4;
}

void parcast::WindowLevelSetting::SetSize(int* size)
{
	m_size[0] = size[0];
	m_size[1] = size[1];
	UpdateScaling();
}

void parcast::WindowLevelSetting::SetCurrentWindowLevel(misWindowLevelStr winLevStr)
{
	m_CurrentLevelWindow = winLevStr;

}

void parcast::WindowLevelSetting::SetDefaultWindowLevel(misWindowLevelStr winLevStr)
{
	m_InitialLevelWindow = winLevStr;
	m_CurrentLevelWindow = m_InitialLevelWindow;
}

misWindowLevelStr parcast::WindowLevelSetting::GetCurrentWindowLevel() const
{
	return m_CurrentLevelWindow;
}

void parcast::WindowLevelSetting::Update(const parcast::Point<int, 2>& startPosition,
                                                  const parcast::Point<int, 2>& currentPosition)
{
	double dx, dy;

	if(m_IsContrastInteractionActive)
	{
		
		dx = m_Scaling * (m_PrevStartPosition[0] - currentPosition[0]) / m_size[0];
		dy = m_Scaling * (m_PrevStartPosition[1] - currentPosition[1]) / m_size[1];
	}
	else
	{
		dx = m_Scaling * (startPosition[0] - currentPosition[0]) / m_size[0];
		dy = m_Scaling * (startPosition[1] - currentPosition[1]) / m_size[1];
	}

	const auto window = m_CurrentLevelWindow.GetWindowWidth();
	const auto level = m_CurrentLevelWindow.GetWindowCenter();
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
		dx = dx * (5 * window / 100);
	}

	if (fabs(dy) < minValueChange)
	{
		dy = sign(dy);
		dy = dy * minValueChange;
	}
	else if (fabs(dy) < (5 * level / 100))
	{
		dy = sign(dy);
		dy = dy * (5 * level / 100);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	// Abs so that direction does not flip
	if (window < 0.0)
	{
		dx = -1 * dx;
	}
	if (level < 0.0)
	{
		dy = -1 * dy;
	}

	// Compute new window level

	double newWindow = dx + window;
	double newLevel = dy + level;

	m_CurrentLevelWindow.SetWindowParams(newLevel, newWindow);
	m_PrevStartPosition[0] = currentPosition[0];
	m_PrevStartPosition[1] = currentPosition[1];
}

 
void parcast::WindowLevelSetting::SetContrastInteraction(bool cntr)
{
	m_IsContrastInteractionActive = cntr;
}

bool parcast::WindowLevelSetting::GetContrastInteraction()
{
	return m_IsContrastInteractionActive;
}
