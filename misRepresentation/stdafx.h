#pragma once

// Windows headers
#include <objidl.h>

#include <gdiplus.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iosfwd>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "boost/chrono.hpp"
#include "boost/filesystem.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "GL/glew.h"
// TGT headers
#include "tgt/camera.h"
#include "tgt/filesystem.h"
#include "tgt/tgtmath.h"
#include "tgt/transfunc.h"
#include "tgt/transfuncintensity.h"
#include "tgt/vector.h"



#include <tchar.h>
#include "itkBoundingBox.h"
#include "itkMutexLock.h"
#include "itkPoint.h"

// VTK headers
#include "vtk3DS.h"
#include "vtkActor.h"
#include "vtkActor2D.h"
#include "vtkAlgorithmOutput.h"
#include "vtkAppendPolyData.h"
#include "vtkAxisActor2D.h"
#include "vtkBox.h"
#include "vtkCaptionActor2D.h"
#include "vtkCellArray.h"
#include "vtkConeSource.h"
#include "vtkCoordinate.h"
#include "vtkCubeSource.h"
#include "vtkCylinderSource.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkFloatArray.h"
#include "vtkFollower.h"
#include "vtkImporter.h"
#include "vtkImporter.h"
#include "vtkInteractorObserver.h"
#include "vtkInteractorStyleImage.h"
#include "vtkLineSource.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLActor.h"
#include "vtkOpenGLActor.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkOpenGLTexture.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPlaneSource.h"
#include "vtkPointData.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkProp.h"
#include "vtkProp3D.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkSTLReader.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkTextureMapToPlane.h"
#include "vtkTexturedSphereSource.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTubeFilter.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWindow.h"
#include "vtkRenderer.h"

#include "igstkMacros.h"
#include "igstkStateMachine.h"
#include "igstkTracker.h"
#include "igstkTrackerTool.h"

#pragma warning( push )
#pragma warning( disable : 4482 )


#include "GL\glew.h"

//Serialization headers
#include "TinyXml/tinyxml.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
#pragma warning( pop )

// Voreen headers
#include "voreen/canvasrenderer.h"
#include "voreen/meshentryexitpoints.h"
#include "voreen/multivolumeproxygeometry.h"
#include "voreen/processor.h"
