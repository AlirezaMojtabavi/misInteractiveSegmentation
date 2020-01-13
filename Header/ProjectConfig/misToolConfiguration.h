#pragma once

#include "misStrctConnectOption.h"
#include "misStructTrackingSetting.h"

class misToolConfiguration
{
public:
	misToolConfiguration(void);
	~misToolConfiguration(void);
	//misToolPropertiesListTypdef ReadStrctToolData(std::string romFilePath);
	misStrctComConnectionOptions	GetConnection();
	misStructTrackingSetting GetTrackingSetting();
	void SetTrackingSetting(misStructTrackingSetting trackingSetting);
	//misSimpleToolNameListTypdef GetAllAvalaibleTools();
	std::vector<std::string>			GetStartUpLoadedTools();

	void UpdateToolsNameXMLFile(std::string romFilePath);
	void ReadToolDataInformationAndConnectionOptions(const std::vector<std::string>& tools);

private:
	void ReadStrctToolDataToConnect(std::string romFilePath);
	misStrctComConnectionOptions	 m_Connection;
	misStructTrackingSetting m_TrackingSetting;

};

