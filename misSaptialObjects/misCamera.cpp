#include "stdafx.h"
#include "..\Header\misCamera.h"


misCamera::misCamera()
{
 
}


misCamera::misCamera(double * position, double * focal, double * viewUp)

{
	for (int i = 0; i < 3; i++)
	{
		m_Position[i] = position[i];
		m_Focal[i] = focal[i];
		m_ViewUP[i] = viewUp[i];
	}
}

misCamera::~misCamera()
{
}

parcast::Vertex<double, 3> misCamera::GetPosition()const
{
	return m_Position;

}

parcast::Vertex<double, 3> misCamera::GetFocal()const
{
	return m_Focal;
}

parcast::Vector<double, 3> misCamera::GetViewUp()const
{
	return m_ViewUP;

}

parcast::Vector<double, 3> misCamera::GetCameraDirection() const
{
	return  m_Position - m_Focal;

}
