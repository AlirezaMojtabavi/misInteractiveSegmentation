#ifdef MISAPPCONTROL_STATIC 
#define MISAPPCONTROLEXPORT  
#else
#ifdef MISAPPCONTROL_DLLEXPORT
#define MISAPPCONTROLEXPORT __declspec(dllexport)
#else
#define MISAPPCONTROLEXPORT __declspec(dllimport)
#endif
#endif


