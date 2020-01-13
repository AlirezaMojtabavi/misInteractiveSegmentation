#pragma once


#include "misLicenseStrct.h"



class   misLicenseTest
{
public:
	static bool      CheckLicense(std::string liFileName,LicenseInformation* liInfo = 0);
	static std::string    GetProUI    ( misUserLicenseStrct userInfo,long long  int val );
	static long long int GetTimer(std::string key);
	static           int GetComparision  (std::string mainKey , std::string muteKey  );
	static           int CheckComparision(std::string mainKey , std::string muteKey, int index);
	static std::string ConvertStringToCode(LicenseInformation licenseInfo,  long long int val /*= -1*/,int useConter /*= -1*/);		
	static std::string ConvertStringToCode(misUIDForLicenseStrct uids);
};

