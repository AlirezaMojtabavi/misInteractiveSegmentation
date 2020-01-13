#pragma once
#include "misApplicationSetting.h"

class misToolFileAddressUtility
{

	misToolFileAddressUtility(void);
	~misToolFileAddressUtility(void);
public:
	
	static std::string MakeRomFilePathAndName(std::string ToolName);
	static std::string MakeStlFilePathAndName(std::string ToolName);

	static std::string MakeMicronTrackerCameraCalibrationFileDirectory();
	static std::string MakeMicronTrackerInitializationFilePathAndName(std::string NameOfInitializationFile);
	static std::string MakeMicronTrackerMarkerTemplatesDirectory();
};

