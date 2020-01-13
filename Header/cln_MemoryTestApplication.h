#ifndef cln_MemoryTestApplication_H_HEADER_INCLUDED_B967EC7F
#define cln_MemoryTestApplication_H_HEADER_INCLUDED_B967EC7F
//##ModelId=4698C6BC02C1

#include "misCommonHeader.h"

class MISCOMMONEXPORT cln_MemoryTestApplication

{
private:
	cln_MemoryTestApplication();

public:
	static cln_MemoryTestApplication* GetInstance();

	size_t GetProccessMemoryConsumeInMegaByte();
	size_t GetProccessMemoryConsumeInMegaByteByRam();
	size_t GetProccessMemoryConsumeInMegaByteByGpu();
	size_t GetProccessMemoryConsumeInMegaByteTotally();
	std::string GetMemoryState();
	size_t GetProccessMemoryConsumeInByte();
	//##ModelId=4698CB7000CB
	size_t  GetBiggestMemeoryBlockSize( void );
	//##ModelId=4698CB7000EA
	virtual ~cln_MemoryTestApplication();
};

#endif /* cln_MemoryTestApplication_H_HEADER_INCLUDED_B967EC7F */
