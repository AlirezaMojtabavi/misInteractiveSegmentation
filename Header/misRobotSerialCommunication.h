#pragma once
#include "igstkSerialCommunicationForWindows.h"
#include "igstkMacros.h"
#include "igstkCommunication.h"
#include "igstkevents.h"
#include <string>
#include "misEvent.h"
#include "vtkIOStreamFwd.h"
#include "RobotEvent.h"

//igstkLoadedEventMacro(misRobotCommandLogCore,misEvent,string);
class misRobotSerialCommunication :
	public  igstk::SerialCommunicationForWindows
{
private:

	misRobotSerialCommunication(void);
	std::ofstream   m_SerilePortStream;
protected:
	/** Write data */
	virtual ResultType InternalWrite( const char *message,
		unsigned int numberOfBytes );

	/** Read data */
	virtual ResultType InternalRead( char *data, unsigned int numberOfBytes,
		unsigned int &bytesRead );

public:
	typedef Communication::ResultType      ResultType;

	/** Macro with standard traits declarations. */
	igstkStandardClassBasicTraitsMacro( misRobotSerialCommunication, igstk::SerialCommunicationForWindows );
	igstkNewMacro(Self);

	~misRobotSerialCommunication(void);
};

