#pragma once


struct misOSIDSrct 
{
	std::string 	ComputerName;
	std::string  OSInstalationData;
	std::string  OSUID;
};


struct  misUIDForLicenseStrct
{
	std::string HardwareUID;
	std::string OSUID;
	std::string SoftwareUID;
	std::string ComputerName;
	std::string SoftVersion;
	misUIDForLicenseStrct()
	{
		HardwareUID="";
		OSUID="";
		SoftwareUID="";
		ComputerName="";
		SoftVersion="";

	}
};

struct  misUserLicenseStrct
{
	std::string LicensedTo;
	std::string LicenseCreationDate;
	std::string LicenseType;
	std::string LicenseValidationDate;
	std::string HDPass;	 
	std::string UIdsLicenseKey;
	std::string LicenseKey;
	misUserLicenseStrct()
	{
		LicensedTo="";
		LicenseCreationDate="";
		LicenseType="";
		LicenseValidationDate="";
		HDPass="";	 
		UIdsLicenseKey="";
		LicenseKey="";

	}
};

struct  LicenseInformation
{
	misUIDForLicenseStrct PrimeryUIDs;
	misUserLicenseStrct   UserData;


};