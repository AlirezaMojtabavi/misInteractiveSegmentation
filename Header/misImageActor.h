#pragma once

#include "misImageGeoProperties.h"
class misImageActor :public vtkOpenGLActor
{
private:
	double  m_Position[3];
public:
	static  misImageActor* New();
	virtual   void GetPosition(double* pos);
	virtual void  GetPlaneCenter(double* arg);
	 virtual void SetPosition (double _arg[3]) ;
	 virtual void SetPosition(double _arg1, double _arg2, double _arg3) ;
	 double*	GetDimention();

	misImageActor(void);
	~misImageActor(void);
	
};

