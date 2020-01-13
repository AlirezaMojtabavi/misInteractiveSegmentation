//#ifdef MISLIBRARY_EXPORT
//#define MISLIBRARYEXPORT __declspec(dllexport)
//#else
//#define MISLIBRARYEXPORT __declspec(dllimport)
//#endif
#ifndef MISLIBRARYEXPORT 
#define MISLIBRARYEXPORT 
#endif