
#include <algorithm>
#include <iosfwd>
#include <sstream>
#include <deque>
#include <memory>
#include <stack>

#include <GL/glew.h>

// Windows Header 
#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#pragma comment (lib,"Gdiplus.lib") 

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "itkEventObject.h"
#include "itkPoint.h"
#include "itkLogger.h"
#include "itkMutexLock.h"

#include "igstkEvents.h"

#include "vtkCharArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkTimeStamp.h"
#include "vtkPolyData.h"

#include "TinyXml//tinyxml.h"

#include "tgt/TransFuncIntensity.h"
#include "tgt/gpucapabilities.h"
#include "tgt/texture.h"
#include "tgt/vector.h"

#include "Serialization/xmlserializer.h"
#include "Serialization/xmldeserializer.h"

