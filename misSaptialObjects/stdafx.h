// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

//#pragma warning( push )
// Comment out if headers included from third party libraries do not generate warnings
// #pragma warning( disable : 4150 )

// STL Headers
#include <algorithm>
#include <cmath>
#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
// GL Headers
#include "GL\glew.h"

// Windows Header 
#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#pragma comment (lib,"Gdiplus.lib")

// ITK Headers
#include "itkVector.h"
#include "itkPoint.h"
#include "itkLogger.h"
#include "itkMutexLock.h"
#include "itkImage.h"
#include "itkSmartPointer.h"
#include "itkBoundingBox.h"
#include "itkMutexLock.h"

// IGSTK headers
#include "igstkMacros.h"
#include "igstkEvents.h"
#include "igstkLogger.h"


// TGT Headers
#include "tgt/matrix.h"
#include "tgt/shadermanager.h"
#include "tgt/textureunit.h"
#include "tgt/texture.h"
#include "tgt/tgtmath.h"
#include "tgt/TransFuncIntensity.h"
#include "tgt/vector.h"

#define vtkRenderingCore_AUTOINIT 3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL)

// VTK Headers
#include "vtkactor.h"
#include "vtkOpenGLActor.h"
#include "vtkActor.h"
#include "vtkActor2D.h"
#include "vtkAssemblyNode.h"
#include "vtkAssemblyPath.h"
#include "vtkCallbackCommand.h"
#include "vtkCamera.h"
#include "vtkCaptionActor2D.h"
#include "vtkCellArray.h"
#include "vtkCellPicker.h"
#include "vtkConeSource.h"
#include "vtkCoordinate.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkFollower.h"
#include "vtkLineSource.h"
#include "vtkMapper.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLActor.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricTorus.h"
#include "vtkParametricSpline.h"
#include "vtkPlane.h"
#include "vtkPlaneSource.h"
#include "vtkPlaneWidget.h"
#include "vtkPlanes.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRegularPolygonSource.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkImageGridSource.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkImageCast.h"
#include "vtkVertexGlyphFilter.h"
#include "vtkPointData.h"

// tgt header 
#include "tgt/filesystem.h"

// Serialization headers
#include "serialization/serializable.h"
#include "tinyXml/tinyxml.h"
#include "tgt/vector.h"
#include "serialization/xmldeserializer.h"
#include "serialization/xmlserializer.h"

// Other Headers
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "targetver.h"

//#pragma warning( pop )