#ifndef __igstk_SystemInformation_h
#define __igstk_SystemInformation_h

/* #undef IGSTK_USE_FLTK */

/* #undef IGSTK_USE_MicronTracker */

/* #undef IGSTK_USE_Qt */

/* #undef IGSTK_USE_OpenIGTLink */

/* #undef IGSTK_USE_VideoImager */

/* #undef IGSTK_USE_OpenCV */

#define IGSTK_DATA_ROOT
#ifdef IGSTK_DATA_ROOT
#  undef IGSTK_DATA_ROOT
#  define IGSTK_DATA_ROOT "D:/API/API_Source/igstk 4.2 changed/Testing/Data"
#else
#  undef IGSTK_DATA_ROOT
#endif

#define IGSTK_BINARY_DIR "D:/API/API_Build/igstk"
#define IGSTK_TEST_OUTPUT_DIR "D:/API/API_Build/igstk/Testing/Temporary"

/* #undef IGSTK_TEST_AURORA_ATTACHED */
#define IGSTK_TEST_AURORA_PORT_NUMBER \
    igstk::SerialCommunication::PortNumber0

/* #undef IGSTK_TEST_POLARIS_ATTACHED */
#define IGSTK_TEST_POLARIS_PORT_NUMBER \
    igstk::SerialCommunication::PortNumber0

/* #undef IGSTK_TEST_LOOPBACK_ATTACHED */
#define IGSTK_TEST_LOOPBACK_PORT_NUMBER \
    igstk::SerialCommunication::PortNumber1

#endif
