#pragma once

struct misN4VStateVarible
{
public:
	double m_WidgetDifference[3];


	int			 m_CurrentZoomPercentage;
	int          m_Counter;
	int          m_AveragingCount;
	int			 vCount;
	GLint		 m_TFid;
	bool m_AppendAxial,m_AppendCoronal,m_AppendSagittal;
	bool         m_FocalPointCenter;
	bool		 m_Active;
	bool		 m_RealTimeMode;
	bool		 m_Updating;
	bool		 m_ModifiedPosition;
	bool		 m_InUpdatingImagePosition;
	bool		 m_HeadRestState;				//this variable is used for SetImage() After Remove Headrest and after  Remove Headrest (true means we are just doing remove/reset headrest)
	bool	     IsRedo;
	bool		 m_IsPointSelectObserverAdded;
	bool		 m_IsPointWidgetObserverAdded;

	double		 m_SurfaceRepBounds[6];
	double		 m_CurrentZoomProportion;
	/*double       m_time1,m_time2,m_time3,m_time4,m_timeRender;*/
	bool   m_PrintTimingReport;
	int m_NumberOfGeneralTimers;
	std::vector<vtkTimerLog*> m_GeneralTimers;
	std::vector<std::string>  m_GeneralTimersString;
	std::vector<bool>         m_UsedGerenalTimers;
	std::vector<double>        m_GeneralAccumulatingTime;
	std::vector<double>        m_GeneralAverageTime;
	double*				m_RangeOfSegmentedObjects;
	bool                m_InitializedViewer;
	misN4VStateVarible(void);
	~misN4VStateVarible(void);
};

