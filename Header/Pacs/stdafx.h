#pragma once

#if defined(_WINDOWS)
	#if !defined (_SCL_SECURE_NO_WARNINGS)
		#define _SCL_SECURE_NO_WARNINGS
	#endif
	#if !defined (_CRT_SECURE_NO_WARNINGS)
		#define _CRT_SECURE_NO_WARNINGS
	#endif
#else
	#if defined(__DEPRECATED)
		#undef __DEPRECATED
	#endif
#endif

#if defined(_WINDOWS) && defined(_GINKGO_DEBUG)
#if defined _GINKGO_CHECK_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif
#endif

#if defined(_WINDOWS)
	#include <stdlib.h>
	#include <sys/types.h>
	#include <winsock2.h>
	#include <windows.h>
#else // !_WIN32
	#include <sys/socket.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif

#if !defined(__cplusplus)
	#include <stdio.h>
#else

	#include <algorithm>
	#include <cmath>
	#include <cstdio>
	#include <cstdlib>
	#include <ctime>
	#include <deque>
	#include <iostream>
	#include <limits>
	#include <list>
	#include <map>
	#include <set>
	#include <sstream>
	#include <stack>
	#include <string>
	#include <vector>
	
	#include <itkImage.h>
	#include <itkExceptionObject.h>
	#include <itkExceptionObject.h>
	#include <itkSmartPointer.h>
	#include <vtkInformation.h>
	#include <vtkAlgorithmOutput.h>
	#include <vtkImageData.h>
	#include <vtkMatrix4x4.h>

	#include "tgt/matrix.h"
	#include "tgt/vector.h"

	#include <api/api.h>
	#include <api/autoptr.h>
	
	
	#include "tinyxml.h"
	#include "serializable.h"
	#include "xmldeserializer.h"
	#include "xmlserializer.h"
#endif
