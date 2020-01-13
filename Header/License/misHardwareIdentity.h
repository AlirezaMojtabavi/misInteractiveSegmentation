#pragma once
#pragma comment(lib, "comsuppw.lib")



class     misHardwareIdentity
{

	
public:
	struct misHardwareInformation
	   {
		   std::string CPUID;
		   std::string HardDriveID;
		   std::string VideoControllerID;
		   std::string MACAddress;
		   std::string GetUniquId();
	   };

misHardwareInformation  GetHardwareSystemSnapShot();
	
	misHardwareIdentity(void);
	~misHardwareIdentity(void);
	
	friend std::ostream;

private:

	IWbemLocator * m_pIWbemLocator ;
	IWbemServices * m_pWbemServices ;
	bool  InitiateServer();
	std::string  GetCpuId();
	std::string  GetSystemID();

	IEnumWbemClassObject* RunQuery(std::wstring  query);

	VARIANT  ExtractPropFromQuery( IWbemClassObject* pClassObject, std::wstring   qurystring);

	IWbemClassObject* GetNextClassObject( IEnumWbemClassObject * pEnumObject);

	std::string  GetHardDriveId();
	std::string  GetMacAddress();
	std::string  GetVidoControllerID();
	bool  m_ReadyToQuery;


};
	  std::ostream& operator<< (std::ostream& stream,  misHardwareIdentity::misHardwareInformation& valid);	
 