// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>

#include <boost/any.hpp>
#include <boost/chrono.hpp>
#include "boost/optional.hpp"
#include "boost/variant.hpp"

#include "GL/glew.h"

#include "tgt/TransFuncIntensity.h"
#include "tgt/camera.h"
#include "tgt/matrix.h"
#include "tgt/texture.h"
#include "tgt/transfunc.h"
#include "tgt/vector.h"





#include <DShow.h>
#include <DShowUtil.h>
#include <Dbt.h>
#include <InitGuid.h>
#include <Ks.h>
#include <KsProxy.h>
#include <ObjBase.h>
#include <amvideo.h>
#include <dvdmedia.h>
#include <strsafe.h>
#include <smartptr.h>


#include "vtkactor.h"
#include "vtkOpenGLActor.h"
#include "vtk3DS.h"
#include "vtkAbstractMapper3D.h"
#include "vtkBoxWidget.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkCubeSource.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkImporter.h"
#include "vtkImporter.h"
#include "vtkInteractorStyle.h"
#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkObject.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkParametricTorus.h"
#include "vtkPicker.h"
#include "vtkPlaneWidget.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPointWidget.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkSmartPointer.h"
#include "vtkSmartPointer.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkwin32OpenGLRenderWindow.h"

#include "igstkEvents.h"
#include "igstkMacros.h"
#include "igstkPulseGenerator.h"
#include "igstkTracker.h"
#include "igstkTrackerTool.h"
#include "itkBinaryFillholeImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkBoundingBox.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkEventObject.h"
#include "itkFastMarchingImageFilter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkHistogram.h"
#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkImageToVTKImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkLaplacianImageFilter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkMutexLock.h"
#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkObject.h"
#include "itkPoint.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkThresholdSegmentationLevelSetFunction.h"
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkVector.h"
#include "itkZeroCrossingImageFilter.h"
#include "vtkObjectFactory.h"
#include <itkImage.h>
#include <itkImageToHistogramFilter.h>
#include <itkImageToVTKImageFilter.h>
#include <itkMacro.h>
#include <itkVTKImageToImageFilter.h>

#include "tinyxml2.h"

#include "TinyXml/tinyxml.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"

// Voreen headers
#include "canvasrenderer.h"
#include "meshentryexitpoints.h"
#include "multivolumeproxygeometry.h"
#include "observer.h"
#include "processor.h"
#include "volumehandle.h"
#include "volumerenderer.h"