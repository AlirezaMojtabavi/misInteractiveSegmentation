#pragma once

// The class Provide config parameter for help debugging application problems or for output some data related to other 
// applications
class misDebugSettings : public Serializable
{

public:
	misDebugSettings();
	bool m_LoggDetail;
	bool m_LoggerEnabled;
	bool LogEventName;
	bool m_RegDataFromFile;
	bool trackerLog;
	bool logTrackerToolPosition;
	bool Use3DTexture;
	bool showMultipleViewTracker;
	bool realtimeLog;
	bool logMicronDetail;
	std::string debugLevel;
	std::string appRuningMode;//test ,profiling normal
	int testCount;
	std::string testFile;

	//A flag to determine whether the application must generate test files or not
	bool m_IsIntestMode;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	bool GetReadLayoutFromXMl() const;
	void SetReadLayoutFromXMl(bool val);
private:
	bool m_ReadLayoutFromXMl = true;
};
