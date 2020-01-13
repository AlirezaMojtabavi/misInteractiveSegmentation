// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <stack>
#include <stdio.h>
#include <tchar.h>
#include <random>
#include <sstream>

// Windows Header 
#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/chrono.hpp>
#include <boost/variant.hpp>
#include <turtle/mock.hpp>

// TGT Headers
#include "tgt/camera.h"
#include "tgt/filesystem.h"
#include "tgt/matrix.h"
#include "tgt/texture.h"
#include "tgt/transfunc.h"
#include "tgt/transfuncintensity.h"
#include "tgt/vector.h"

// ITK Headers
#include "itkEventObject.h"
#include "itkMatrix.h"
#include "itkMutexLock.h"
#include "itkVector.h"
#include "itkVersor.h"
#include "itkBoundingBox.h"

// VTK headers
#include "vtk3DWidget.h"
#include "vtk3ds.h"
#include "vtkActor.h"
#include "vtkActorCollection.h"
#include "vtkBoxWidget.h"
#include "vtkCamera.h" 
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkImageViewer.h"
#include "vtkImporter.h"
#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkMapper.h"
#include "vtkMatrix4x4.h"
#include "vtkOpenGLActor.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPicker.h"
#include "vtkPlaneWidget.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPolyData.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkProp3D.h"
#include "vtkSmartPointer.h"
#include "vtkTextActor.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"
#include "vtkWin32OpenGLRenderWindow.h"

#include "igstkTransform.h"

#include "TinyXml/tinyxml.h"
#include "tinyxml2.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
#include "voreen\voreenapplication.h"

// IGSTK Headers
#include "igstkMacros.h"
#include "igstkEvents.h"
#include "igstkLogger.h"

#include "gdcmBinEntry.h"
#include "gdcmDicomDir.h"
#include "gdcmDicomDirImage.h"
#include "gdcmDicomDirMeta.h"
#include "gdcmDicomDirPatient.h"
#include "gdcmDicomDirSerie.h"
#include "gdcmDicomDirStudy.h"

// Voreen headers
#include "voreen/canvasrenderer.h"
#include "voreen/meshentryexitpoints.h"
#include "voreen/multivolumeproxygeometry.h"
#include "voreen/observer.h"
#include "voreen/processor.h"
#include "voreen/volumehandle.h"
#include "voreen/volumerenderer.h"

// TODO: reference additional headers your program requires here
