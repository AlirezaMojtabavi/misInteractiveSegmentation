#include "StdAfx.h"
#include "misImageActor.h"

#include "misImageSlicerMapper.h"

misImageActor::misImageActor(void)
{
}

misImageActor::~misImageActor(void)
{
	
}

void misImageActor::GetPosition(double* pos)
{
	for(int i=0;i<3;i++)
		pos[i]=m_Position[i];
}

misImageActor* misImageActor::New()
{
	return  new misImageActor;
}

void misImageActor::SetPosition( double _arg[3] )
{ 
	SetPosition(_arg[0],_arg[1],_arg[2]);
}

void misImageActor::SetPosition( double _arg1, double _arg2, double _arg3 )
{
	m_Position[0]=_arg1;
	m_Position[1]=_arg2;
	m_Position[2]=_arg3;
}

 

double* misImageActor::GetDimention(  )
{

	misImageSlicerMapper* pMapper = dynamic_cast<misImageSlicerMapper*>(GetMapper());
	if(pMapper)
		return  pMapper->GetDimention();

	return  NULL;
}

 


void misImageActor::GetPlaneCenter( double* arg )
{
	misImageSlicerMapper*  pMapper=dynamic_cast<misImageSlicerMapper*>(GetMapper());
	if(pMapper)
	{
		tgt::vec3  cent= pMapper->GetCenter();
		for (int i=0;i<3;i++)
		{
			arg[i]=cent[i];
		}
	}	

}
