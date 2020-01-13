#pragma once

#include "misDataProdecureEnum.h"
#include "misSimplePointType.h"
#include "BiopsyPlanFlowParam.h"

class  misPlanFlowInformation
{


public:
	misPlanFlowInformation(const PlanFlowParameter planningFlowParam);

 	double*  GetImagePosition(int fps);
	double*	 GetImagePosition(double normalizedVal);
 	double   GetNormalizedValue();
	bool SetPlanFlowInformation(const double startPoint[3] , const double endPoint[3], int stepSize, misCineDirection cineDirection);
 	void ResetPlanFlowInformation();
	
	private:
 	misCineDirection m_Direction;
 	double m_StartPoint[3];
 	double m_EndPoint[3];
	int		m_FlowStepSize;
	int		m_FlowDelay;
	double	m_FlowLength;
	double  m_NormalizedVal;
	misSimplePointType m_CurrentPosition;
};

