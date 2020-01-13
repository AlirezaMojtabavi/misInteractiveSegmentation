#pragma once

#include "misCommonHeader.h"

// The IRecordableData abstract class provides a simple interface to be inherited by classes that contain data that can be recorded
// to a stream.
// Note: Designed as part of the data logging facility.
class MISCOMMONEXPORT IRecordableData
{
	MISCOMMONEXPORT friend std::ostream& operator<<(std::ostream& os, const IRecordableData& recordableData);

public:
	virtual ~IRecordableData(void)
	{
	}

private:
	// This method is called by the friend ostream operator. It must be overridden by subclasses to output the data held by 
	// the concrete object to ostream.
	virtual std::ostream& WriteToStream(std::ostream& os) const = 0;
};
// As a friend function to the IRecordableData class, calls its private member to output the data held by the object to the stream.

MISCOMMONEXPORT std::ostream& operator<<(std::ostream& os, const IRecordableData& recordableData);