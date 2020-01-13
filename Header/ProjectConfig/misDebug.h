#pragma once

// Use MISDBG for runtime evaluation of C++ expressions and printing them out for debugging purposes. It could also be used for
// printing out arbitrary strings
// Usage: 
//		MISDBG ( argumentCount, arg1, arg2, ..., argN )
//		arg = MISDARG(expression)    or    arbitraryString
//		argumentCount = total number of arguments arg1 ... argN
// Example:
//		MISDBG(4, "Debug output", MISDARG(myVariable), MISDARG(a + b + c), MISDARG(44 + 555));
//			output from above line is similar to:
//		In MyClass::MyFunction (line 45) =>  Debug output  ,  myVariable = 123  ,  a + b + c = 54324  ,  44 + 555 = 599
//
// When you need a certain [debugging] statement be executed only once out of many times that the point is reached, use 
// MISDBGHITCNT specifying the number of hit counts along with the statement.
// Example:
//		for (int i = 0; i < MAX; ++i)
//		{
//			MISDBGHITCNT(5) MISDBG(1, MISDARG(i));
//			// other statements
//		}
//			in the above line, the debug output will only be generated for on each 5th hit of the line, that is it will output
//			i = 4, i = 9, i = 14 ...
inline void misDebugOutput(const std::string &description, int count, ...) 
{
	std::cout << description;
	va_list args;
	va_start(args, count);
	if (count > 0)
		std::cout << " =>  ";
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, std::string);
		if (i + 1 < count)
			std::cout << "  ,  ";
	}
	va_end(args);
	std::cout << std::endl;
}

#ifdef _DEBUG
#ifndef DEFINE_MIS_DEBUG_MACROES
#define DEFINE_MIS_DEBUG_MACROES
#endif
#endif

#ifdef DEFINE_MIS_DEBUG_MACROES

#define MISDBG(COUNT, ...) \
{	\
	std::stringstream sBuilder;	\
	sBuilder << "In " << __FUNCTION__ << " ( line " << __LINE__ << " )";	\
	misDebugOutput(sBuilder.str(), COUNT, __VA_ARGS__);	\
}

#define MISDBGHITCNT(HITCOUNT) \
	static int hitCount = 1;	\
	if (++hitCount % HITCOUNT == 0)


#define MISDARG(ARG) (dynamic_cast<const std::stringstream&>(std::stringstream() << #ARG << " = " << (ARG)).str())

#define PDBGSKEL(EXPARGS) \
{\
	std::ostringstream strm; \
	strm << __FUNCTION__ << "(" << __LINE__ << "): " EXPARGS << std::endl; \
	std::cout << strm.str(); \
}

#define PDBGEXPARG(ARG) << " |< " << #ARG << " = " << (ARG) << " >| "

#define PDBGS PDBGSKEL()
#define PDBGM(MSG) PDBGSKEL(<< MSG)
#define PDBG1(ARG1) PDBGSKEL(PDBGEXPARG(ARG1))
#define PDBG2(ARG1, ARG2) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2))
#define PDBG3(ARG1, ARG2, ARG3) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3))
#define PDBG4(ARG1, ARG2, ARG3, ARG4) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) PDBGEXPARG(ARG4))
#define PDBG5(ARG1, ARG2, ARG3, ARG4, ARG5) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) \
	PDBGEXPARG(ARG4) PDBGEXPARG(ARG5))
#define PDBG6(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) \
	PDBGEXPARG(ARG4) PDBGEXPARG(ARG5) PDBGEXPARG(ARG6))
#define PDBG7(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) \
	PDBGEXPARG(ARG4) PDBGEXPARG(ARG5) PDBGEXPARG(ARG6) PDBGEXPARG(ARG7))
#define PDBG8(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) \
	PDBGEXPARG(ARG4) PDBGEXPARG(ARG5) PDBGEXPARG(ARG6) PDBGEXPARG(ARG7) PDBGEXPARG(ARG8))
#define PDBG9(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9) PDBGSKEL(PDBGEXPARG(ARG1) PDBGEXPARG(ARG2) PDBGEXPARG(ARG3) \
	PDBGEXPARG(ARG4) PDBGEXPARG(ARG5) PDBGEXPARG(ARG6) PDBGEXPARG(ARG7) PDBGEXPARG(ARG8) PDBGEXPARG(ARG9))

#else

#define MISDBG(COUNT, ...)
#define MISDBGHITCNT(HITCOUNT)
#define MISDARG(ARG)

#define PDBGS 
#define PDBGM(MSG) 
#define PDBG1(ARG1) 
#define PDBG2(ARG1, ARG2) 
#define PDBG3(ARG1, ARG2, ARG3) 
#define PDBG4(ARG1, ARG2, ARG3, ARG4) 
#define PDBG5(ARG1, ARG2, ARG3, ARG4, ARG5) 

#endif