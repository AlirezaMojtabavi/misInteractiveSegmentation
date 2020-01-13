#pragma once

#include <boost/chrono.hpp>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <math.h>
#include <memory>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <gl/glew.h>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <objidl.h>

#include <gdiplus.h>

#include "boost/filesystem.hpp"
#include "boost\lexical_cast.hpp"
#include "boost\optional.hpp"

#include "itkBoundingBox.h"
#include "itkImage.h"
#include "itkLogger.h"
#include "itkMutexLock.h"
#include "itkNeighborhoodConnectedImageFilter.h"

#include "vtk3DS.h"
#include "vtkImporter.h"
#include "vtk3DWidget.h"
#include "vtkAbstractWidget.h"
#include "vtkActor.h"
#include "vtkActor2D.h"
#include "vtkAppendPolyData.h"
#include "vtkAssemblyNode.h"
#include "vtkAssemblyPath.h"
#include "vtkBox.h"
#include "vtkBoxWidget.h"
#include "vtkCallbackCommand.h"
#include "vtkCamera.h"
#include "vtkCameraInterpolator.h"
#include "vtkCaptionActor2D.h"
#include "vtkCell.h"
#include "vtkCellArray.h"
#include "vtkCellPicker.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkCoordinate.h"
#include "vtkCylinderSource.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkFollower.h"
#include "vtkHandleRepresentation.h"
#include "vtkHandleWidget.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkInteractorObserver.h"
#include "vtkLine.h"
#include "vtkLineRepresentation.h"
#include "vtkLineSource.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkObject.h"
#include "vtkObjectFactory.h"
#include "vtkPNGReader.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPerspectiveTransform.h"
#include "vtkPicker.h"
#include "vtkPlanes.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkProp.h"
#include "vtkProp3D.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkPropPicker.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkTextProperty.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTubeFilter.h"
#include "vtkVectorText.h"
#include "vtkWidgetCallbackMapper.h"
#include "vtkWidgetEvent.h"
#include "vtkWidgetEventTranslator.h"
#include "vtkWidgetRepresentation.h"
#include "vtkWindow.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkWin32OpenGLRenderWindow.h"

#include "igstkEvents.h"
#include "igstkMacros.h"

#include "tgt/matrix.h"
#include "tgt/vector.h"
#include "tgt/filesystem.h"
#include "tgt/texture.h"
#include "tgt/transfuncintensity.h"

#include "TinyXml/tinyxml.h"
#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"