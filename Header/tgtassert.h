#pragma  once

bool myCustomAssert(long line, const char* filename, const char* functionName,
                        const char* description, bool& always);

   #define tgtAssert(e, description) \
	_ASSERT(e);\
	std::cout<<description
