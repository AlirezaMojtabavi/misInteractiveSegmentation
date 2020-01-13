#include "StdAfx.h"
#include "misAxisProperty.h"

misAxisProperty::misAxisProperty( double xLenghth, double yLenghth, double zLength )
	:x_Lenght(xLenghth), y_Lenght(yLenghth), z_Lenght(zLength)
{
	m_GeoType=cylinder;
	m_CylinderRadius=10;
	m_spherRadius=10;
	m_ScaleFactor=10;
}
 