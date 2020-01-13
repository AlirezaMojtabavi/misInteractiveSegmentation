#ifndef __MISSTRINGTOOLS__
#define __MISSTRINGTOOLS__

#include "misCommonHeader.h"

typedef std::string misUID;
typedef unsigned int misID;

class MISCOMMONEXPORT misStringTools
{
public:
	static misUID GenerateNewUID();
	static std::string IntToString(int intValue);
	static std::string FloatToString(float doubleValue);
	static std::string GetCurrentDatePlusTime();
};
#endif
