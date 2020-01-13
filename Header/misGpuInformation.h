#pragma once

#include "misCommonHeader.h"

class MISCOMMONEXPORT misGpuInformation
{
private:

		int m_dedVideoMem;

		int m_totalAvailableMem;

		int m_curAvailableMem;
 		int m_evictionCount;
		int m_evictedMem;
public:

	int GetDedVideoMem()  ;
	int GetTotalAvailableMem()  ;
	int GetCurAvailableMem()  ;

	misGpuInformation(void);

	//update mem  value in kb
	void UpdateInformation();
	~misGpuInformation(void);
};
