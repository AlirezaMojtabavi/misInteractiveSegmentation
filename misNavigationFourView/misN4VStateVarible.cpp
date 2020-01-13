#include "StdAfx.h"
#include "misN4VStateVariable.h"

misN4VStateVarible::misN4VStateVarible(void)
{
// 	m_time1 = 0;
// 	m_time2 = 0;
// 	m_time3 = 0;
// 	m_time4 = 0;
	this->m_Counter =0;
//	m_timeRender=0;
	m_AveragingCount = 50;
	m_FocalPointCenter=false;
	m_PrintTimingReport = true;
	m_NumberOfGeneralTimers = 10;
	m_Active=false;
	this->m_RealTimeMode = false;
	this->m_CurrentZoomPercentage = 100;
	this->m_CurrentZoomProportion = 1;
	this->vCount=0;
	this->IsRedo = false;
	this->m_HeadRestState = false;
// 	for (int i=0;i<3;i++)
// 	{
// 		this->m_AxialwidgetDiffrence[i]		=0;
// 		this->m_CornalwidgetDiffrence[i]	=0;
// 		this->m_SagitalwidgetDiffrence[i]	=0;
// 	}
	m_Updating							=false;
	m_InUpdatingImagePosition			=false;
// 	m_ParallelSettingAppliedAxail		=false;
// 	m_ParallelSettingAppliedAxail=false;
// 
// 	m_ParallelSettingAppliedCoranal		=false;
// 	m_ParallelSettingAppliedSaggital	=false;
// 	m_ParallelSettingAppliedCoranal=false;
// 	m_ParallelSettingAppliedSaggital=false;
	m_AppendAxial=true;
	m_AppendCoronal=true;
	m_AppendSagittal=true;
	this->m_RangeOfSegmentedObjects = new double[2];
	this->m_RangeOfSegmentedObjects[0]=0;
	this->m_RangeOfSegmentedObjects[1]=0;
	m_IsPointSelectObserverAdded		=false;
	m_IsPointWidgetObserverAdded		=false;
	m_InitializedViewer=false;

	m_WidgetDifference[0]= -5;
	m_WidgetDifference[1]= 5;
	m_WidgetDifference[2]= 5;
}


misN4VStateVarible::~misN4VStateVarible(void)
{
}
