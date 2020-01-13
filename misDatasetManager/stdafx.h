// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <chrono>

#include <boost/variant/detail/substitute.hpp>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <objidl.h>
#include <GdiPlus.h>
#include <Rpc.h>
#include <crtdbg.h>

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "GL/glew.h"

#include "gdcmDicomDir.h"

#include "itkEventobject.h"
#include "itkMutexLock.h"
#include "itkSmartPointer.h"
#include "itkBoundingBox.h"

#include "vtkActorCollection.h"
#include "vtkImageAccumulate.h"
#include "vtkCellData.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkImageCast.h"
#include "vtkImageReslice.h"
#include "vtkImageThreshold.h"
#include "vtkImageViewer2.h"
#include "vtkInteractorStyleImage.h"
#include "vtkLookupTable.h"
#include "vtkMatrix4x4.h"
#include "vtkParametricSpline.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"

#include "igstkMacros.h"
#include "igstkevents.h"
#include "igstklogger.h"

#include "tgt/matrix.h"
#include "tgt/vector.h"
#include "tgt/TransFuncIntensity.h"
#include "tgt/transfuncmappingkey.h"

#include "TinyXml/tinyxml.h"

#include "tinyxml2.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
