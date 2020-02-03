// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <deque>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <stack>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include  <unordered_map>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <objidl.h>

 
#include <gdiplus.h>

#include "boost/chrono.hpp"
#include "boost/variant.hpp"
#include <boost/optional.hpp>

#include "GL/glew.h"
#undef ITK_HAVE_FENV_H
#include "itkBoundingBox.h"
#include "itkEventObject.h"
#include "itkMatrix.h"
#include "itkMutexLock.h"
#include "itkPoint.h"
#include "itkVector.h"

#define vtkRenderingCore_AUTOINIT 3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL) 

#include "vtk3DS.h"
#include "vtk3DWidget.h"
#include "vtkActorCollection.h"
#include "vtkAngleRepresentation2D.h"
#include "vtkAngleWidget.h"
#include "vtkBoxWidget.h"
#include "vtkCallbackCommand.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkContourFilter.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkExtractVOI.h"
#include "vtkFollower.h"
#include "vtkImageData.h"
#include "vtkImageReader.h"
#include "vtkImageReader2.h"
#include "vtkImporter.h"
#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLight.h"
#include "vtkLightCollection.h"
#include "vtkMapper.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLRenderer.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPicker.h"
#include "vtkPlaneWidget.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPointPicker.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkPolyDataWriter.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkSetGet.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkSphereSource.h"
#include "vtkSplineWidget.h"
#include "vtkTextActor.h"
#include "vtkTransform.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkproperty2D.h"
#include <vtkCaptionActor2D.h>
#include <vtkCubeSource.h>
#include <vtkOpenGLActor.h>
#include <vtkPolyDataMapper.h>
#include <algorithm>
#include <iostream>
#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"
#include "vtkImageReslice.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include <vtkDICOMImageReader.h>
#include <vtkImageMapper3D.h>
#include "vtkCamera.h"
#include "vtkRendererCollection.h"
#include "vtkContextActor.h"
#include <itkVTKImageToImageFilter.h>
#include "itkBinaryFillholeImageFilter.h"
#include <itkImageToVTKImageFilter.h>
#include <vtkImageSliceMapper.h>
#include "itkCastImageFilter.h"
#include "vtkObjectFactory.h"
#include "itkFastMarchingImageFilter.h"
#include "itkZeroCrossingImageFilter.h"
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include <itkImage.h>
#include <itkMacro.h>
#include "itkThresholdSegmentationLevelSetFunction.h"
#include "itkImageRegionIterator.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkLaplacianImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkHistogram.h"
#include <itkImageToHistogramFilter.h>
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkBinaryThresholdImageFilter.h" 
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "MySpeedFunction3D.h"
 
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmBinEntry.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDir.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDirImage.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDirMeta.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDirPatient.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDirSerie.h"
#include "C:/Program Files/GDCM/include/gdcm-1.2/gdcmDicomDirStudy.h"


#include "igstkEvents.h"
#include "igstkPulseGenerator.h"

#include "tgt/matrix.h"
#include "tgt/transfunc.h"
#include "tgt/transfuncintensity.h"
#include "tgt/vector.h"
#include "tgt/transfuncmappingkey.h"


#include "gdcmDicomDir.h"

#include "voreen/canvasrenderer.h"
#include "voreen/meshentryexitpoints.h"
#include "voreen/multivolumeproxygeometry.h"
#include "voreen/port.h"
#include "voreen/processor.h"
#include "voreen/volume.h"
#include "voreen/volumehandle.h"
#include "voreen/voreenapplication.h"
#include "voreen/voreenmodule.h"
 
#include "tinyxml2.h"
#include "tinyxml/tinyxml.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"
// TODO: reference additional headers your program requires here
