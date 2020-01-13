#ifdef MISDCMTKHEADER_MISDLLEXPORT

#define MISDCMTKEXPORT __declspec(dllexport)
#else
#define MISDCMTKEXPORT __declspec(dllimport)
#endif