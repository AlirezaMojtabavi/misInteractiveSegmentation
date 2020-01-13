#pragma once

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <list>
#include <memory>
#include <sstream>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "boost/chrono.hpp"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "GL\glew.h"
// Windows Header 
#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#pragma comment (lib,"Gdiplus.lib")

#include "itkLoggerBase.h"
#include "itkMutexLock.h"
#include "itkPoint.h"
#include "itkVector.h"
#include "vnl\vnl_matrix.h"
#include "vnl\vnl_vector.h"

#define vtkRenderingCore_AUTOINIT 3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL) 

#include "vtk3DS.h"
#include "vtkActorCollection.h"
#include "vtkAppendPolyData.h"
#include "vtkCamera.h"
#include "vtkClipPolyData.h"
#include "vtkImageData.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkImporter.h"
#include "vtkLookupTable.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkOBJReader.h"
#include "vtkPNGReader.h"
#include "vtkPlane.h"
#include "vtkPointdata.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkSTLReader.h"
#include "vtkSTLReader.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkTexture.h"
#include "vtkTexture.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkWindows.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkBoxWidget.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkPicker.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkAbstractWidget.h"
#include "vtkPlaneWidget.h"
#include "vtkInteractorStyleImage.h"
#include "vtkDistanceWidget.h"
#include "vtkPointHandleRepresentation2D.h"

#include "itkBoundingBox.h"

#include "igstkEvents.h"

#include "tinyxml/tinyxml.h"

#include "tgt/filesystem.h"
#include "tgt/matrix.h"
#include "tgt/vector.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"