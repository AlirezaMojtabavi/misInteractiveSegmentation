#pragma once

#include "misLicenseStrct.h"
 

class     misCodeDecode
{
	friend class misLicenseTest;
private:
	static int DecodeValue( int currentValue , int inbex, int offsetCodding);
	static int CodeValue( int currentValue   , int inbex, int offsetCodding);

	static int CodeDecodeValue60( int currentValue );
	static int CodeDecodeValue45( int currentValue );
	static int CodeDecodeValue30( int currentValue );
	static int CodeDecodeValue10( int currentValue );

	static int CodeDecodeValue( int currentValue , int functionNUmber);

	static std::string ConvertIntToString( int lastValueDIGIT, long long &finalKey, long long &startValue );
	static long long   ConvertStringToInt(std::string str);
	static std::string      FillNumber(std::string inputString, long long int val);
	static std::string      FillCheck (std::string mainKey,std::string muteKey);
	static char        IntToChar(int val);
	static int         CharToInt(char c);
	static int         GetCurrentDigit(long long int val,int digit);
	

public:


	static char*  Code  (const char* buffer,int lenght, int offsetCodding);
	static char*  Decode(const char* buffer,int lenght,int& outlength, int offsetCodding);

	//static std::string ConvertStringToCode(LicenseInformation licenseInfo,  long long int val /*= -1*/,int useConter /*= -1*/);		
	//static std::string ConvertStringToCode(misUIDForLicenseStrct uids);
	
	static std::string ConvertStringToCode(std::string str);	

	static void        UpdateString(std::string &inputStr,double it );
	static int         GetCheckNumber(std::string inputString);
	static std::string      CodedXmlOutput(std::string id,int offsetCodding);
};

