#pragma once


#include "misCommonHeader.h"

//bool operator<(const string& _Left, const string& _Right)
//{
//	int res=strcmp((char*)_Left.c_str(),(char*)_Right.c_str());
//	if (res<0)
//	{
//		return  false;
//	}
//	else
//		return  true;
//
//}
#ifdef  _DEBUG

class  MISCOMMONEXPORT prsDebugVariable
{
private:

		prsDebugVariable(char* Filexml);
public:
	static prsDebugVariable*  GetInstance();

	std::map<std::string, std::string> m_Strings ;

	std::map<std::string, double> m_Variables ;

	double  Value(std::string  labe);
	std::string   ValueString(std::string  labe);

	~prsDebugVariable(void);
};
#endif