#pragma once

#include "IRecordableData.h"
#include "misCommonHeader.h"


// The IDataLogger abstract class provides an interface for logging facilities that can log data at various locations in the code.
// Such facilities can be used in debugging the application - where data is suspect to be invalid.
class MISCOMMONEXPORT IDataLogger
{
public:
	// Determines whether the data logging facility is enabled. If not enabled, no records are appended.
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_IsEnabled, Enabled);

	// Appends a new record with the specified description and recordable data to the underlying log sink. It returns immediately
	// if the logger is not enabled.
	virtual void AppendRecord(const std::string& description, const IRecordableData& data) = 0;

	virtual ~IDataLogger(void) { }

};
