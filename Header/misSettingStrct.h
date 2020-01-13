#pragma once


//#include "misobjectProperitiesEnums.h"
//#include "misTrackingManagerEnums.h"
//#include "misStrctColorData.h"
//#include <deque>
//#include "LevelInformation.h"
//#include "misWindowLevelStr.h"
//#include "misEnumCroppDirection.h"
  #include "misEnums.h"

//using namespace System;

struct misDataBaseSetting
{
	bool LoggerEnabled;
	bool forceToSaveAllContianedOfSoluion;

	misSaveSolutionMode SavingMode;
};

struct misDatlaUploadingSetting
{
	bool LoggerEnabled;

	bool m_UseThredaForFolderAnalysis;
	bool m_UesThredaForDicomReading;

	int  m_MinimumImageNumberIsAccptedForNavigation;
	int  m_AtleastMinimumImageNumberIsAccptedForNavigation;

	double m_MaxImageSpacaingIsAccptedForNavigation;
	double m_MaximumMaxImageSpacaingIsAccptedForNavigation;
};

struct misDataCkeckingSetting
{
	bool LoggerEnabled;
};

struct misSnapShotSetting 
{
	string snapShotFileExtension;
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Path setting////////////////////////////////////////////////
struct misStrctSettingPath
{
	string applicationPath;
	string guiPath;
	string imagePath;

	string ROMFilePath;
	string OBJFilePath;
	string XMLFilePath;

	string COMPortSettingXMLFilePath;

	string logerPath;
	string softwareSettingPath;
	string toolManagerPath;

	string mainData;
	string patientData;
	string listOfPatients;
	string userData;
	string listOfUsers;

	string ComPortSettingFilePath;
	// Note: Default value making by "makePathSetting" function
};







