#ifdef IOLIBMISDLL_EXPORT
#define IOLIBMISDLLEXPORT __declspec(dllexport)
#else
#define IOLIBMISDLLEXPORT __declspec(dllimport)
#endif
