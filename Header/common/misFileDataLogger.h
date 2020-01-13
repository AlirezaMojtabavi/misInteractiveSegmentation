#pragma once

#include "IDataLogger.h"
#include "misCommonHeader.h"

// The misFileDataLogger class, which implements the IDataLogger interface, is a data logger that uses a file as its log sink. 
// Instances of this class cannot be directly created. Rather, only one instance of this class is created through the lifetime of
// the application (singleton). The sink file is created on creation of the singleton instance in the current working directory
// named "DataLog.log".
// WARNING: misFileDataLogger is not thread-safe!
class MISCOMMONEXPORT misFileDataLogger // : public IDataLogger
{
public:
	~misFileDataLogger();

	// Determines whether the data logging facility is enabled. If not enabled, no records are appended.
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_IsEnabled, Enabled);

	template <typename T>
	void AppendRecord(const std::string& description, const T& data)
	{
		if (!Enabled() || !m_LogFileStream.is_open())
			return;

		// Get current system time, format the system time, and output the time, description, and data
		// to the file followed by a newline character.
		std::time_t time = std::time(nullptr);
#pragma warning( suppress : 4996 )
		std::tm tm = *std::localtime(&time);
		m_LogFileStream << std::put_time(&tm, "%Y/%m/%d, %H:%M:%S") << " - " << description << " => " << data << std::endl;
	}

	
	// Gets the singleton instance of the class. The singleton is created on the first call to this method.
	static std::shared_ptr<misFileDataLogger> GetInstance();

	const std::string FileName;

private:
	// Privatized so the class cannot be directly instantiated, use GetInstance() to get the singleton instead.
	// It initializes the logger by calling CreateLogFilePath().
	misFileDataLogger();	
	// The singleton instance of the class; created at first necessity.
	static std::shared_ptr<misFileDataLogger> m_SingletonInstance;

	std::fstream m_LogFileStream;	// File stream used as the log sink.
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		os << vec[i] << ", ";
	}
	return os << vec.back() << "; ";
}

#define MIS_LOG_DATA(DESCRIPTION_STR, DATA_ITEM)	\
{	\
	std::stringstream descriptionStr;	\
	descriptionStr << "At " << __FILE__ << ":" << __LINE__ << "(func: " << __FUNCTION__ << ") : " << ( DESCRIPTION_STR );	\
	misFileDataLogger::GetInstance()->AppendRecord(descriptionStr.str(), DATA_ITEM);	\
}

#define MIS_LOG_DATA_FORCE(DESCRIPTION_STR, DATA_ITEM)	\
{	\
	std::stringstream descriptionStr;	\
	descriptionStr << "At " << __FILE__ << ":" << __LINE__ << "(func: " << __FUNCTION__ << ") : " << ( DESCRIPTION_STR );\
	bool prevStateActivity = misFileDataLogger::GetInstance()->Enabled();	\
	misFileDataLogger::GetInstance()->EnabledOn();\
	misFileDataLogger::GetInstance()->AppendRecord(descriptionStr.str(), DATA_ITEM);	\
	misFileDataLogger::GetInstance()->SetEnabled(prevStateActivity);\
}
