// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>

#include "boost/chrono.hpp"
#include "boost/optional.hpp"

#include <ObjIdl.h>
#include <process.h>
#include <GdiPlus.h>

#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkThresholdImageFilter.h"

#include "vtkImageData.h"
#include "vtkImageWriter.h"
#include "vtkSmartPointer.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"

#include "igstkEvents.h"

// TGT Headers
#include "tgt/matrix.h"

#include "TinyXml/tinyxml.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"

// TODO: reference additional headers your program requires here
