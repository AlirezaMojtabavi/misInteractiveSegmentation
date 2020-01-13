#pragma once

#include "misTrackingManagerTypes.h"

class  UpdateStateObserver: 	public itk::Command
{
private:

	UpdateStateObserver(void);

public:

	typedef UpdateStateObserver			Self;
	typedef itk::SmartPointer<Self>		Pointer;
	//itk::Command						Superclass;
	itkNewMacro(Self);


	bool m_TrackerUpdateStateFailure;

	~UpdateStateObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );

	virtual void Execute( itk::Object *caller, const itk::EventObject & event );

};
//--
class OpenComObserver: 	public itk::Command
{
private:

	OpenComObserver(void);

public:

	typedef OpenComObserver   Self;
	typedef itk::SmartPointer<Self>			Pointer;
	//itk::Command							Superclass;
	itkNewMacro(Self);


	bool m_TrackerOpenSuccess;
	//bool m_TrackerOpenFailure;
	bool m_TrackerStartSuccess;

	~OpenComObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );

	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
};
/////////////////////////////////////////////////////////////////////////////////
//added by -M.A-
class CloseComObserver: 	public itk::Command
{
private:

	CloseComObserver(void);

public:

	typedef CloseComObserver   Self;
	typedef itk::SmartPointer<Self>			Pointer;

	itkNewMacro(Self);

	bool m_TrackerCloseSuccess;
	//bool m_TrackerCloseFailure;

	~CloseComObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );

	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
};
//-------------------------------------------------------------------------------
class TrackerDisconnectObserver: 	public itk::Command
{
private:

	TrackerDisconnectObserver(void);

public:

	typedef TrackerDisconnectObserver   Self;
	typedef itk::SmartPointer<Self>			Pointer;

	itkNewMacro(Self);

	bool m_TrackerConnectionStatus;

	~TrackerDisconnectObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );

	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
};
//-------------------------------------------------------------------------
class StartStopObserver: 	public itk::Command
{
private:

	StartStopObserver(void);

public:

	typedef StartStopObserver   Self;
	typedef itk::SmartPointer<Self>				Pointer;
	//itk::Command								Superclass;
	itkNewMacro(Self);

	bool m_StartSuccess;
	bool m_StartFailure;
	bool m_StopSuccess;
	bool m_StopFailure;

	~StartStopObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );

	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
};

class ToolObserver: 	public itk::Command
{

public:
	typedef ToolObserver   Self;
	typedef itk::SmartPointer<Self>                 Pointer;
	itkNewMacro(Self);

	bool m_AddToolSuccess;
	bool m_RemoveToolSuccess;
	bool m_ConfigureToolSuccess;

	~ToolObserver(void)
	{
	};

	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );
	virtual void Execute( itk::Object *caller, const itk::EventObject & event );

private:
	ToolObserver(void);
};
//-

