/* 
 * here is where system comupted values get stored these values should only
 * change when the target compile platform changes 
 */

#define IGSTK_VERSION_MAJOR 4
#define IGSTK_VERSION_MINOR 0
#define IGSTK_VERSION_PATCH 0
#define IGSTK_VERSION_STRING ""

/* define any platform-specific macros */
/* #undef HAVE_TERMIOS_H */
/* #undef HAVE_TERMIO_H */

/* define some cmake-configurable macros */
#define IGSTK_SERIAL_PORT_0 "COM1:"
#define IGSTK_SERIAL_PORT_1 "COM2:"
#define IGSTK_SERIAL_PORT_2 "COM3:"
#define IGSTK_SERIAL_PORT_3 "COM4:"
#define IGSTK_SERIAL_PORT_4 "COM5:"
#define IGSTK_SERIAL_PORT_5 "COM6:"
#define IGSTK_SERIAL_PORT_6 "COM7:"
#define IGSTK_SERIAL_PORT_7 "COM8:"

/* indicate whether FLTK is being used or not */
/* #undef FLTK_FOUND */

/* indicate whether to use or not the coordinate reference system infrastructure */
/* #undef IGSTK_USE_COORDINATE_REFERENCE_SYSTEM */

/* #undef IGSTK_USE_FLTK */
#define IGSTK_USE_MicronTracker
/* #undef IGSTK_USE_Qt */
/* #undef IGSTK_USE_OpenIGTLink */
/* #undef IGSTK_USE_SceneGraphVisualization */
/* #undef IGSTK_USE_OpenCV */
/* #undef IGSTK_USE_VideoImager */
