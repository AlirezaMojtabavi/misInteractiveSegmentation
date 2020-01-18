#pragma once

#pragma warning (push)
#pragma warning (disable : 4005 4251 4503 4995)
#include <ObjIdl.h>
#include <GdiPlus.h>

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <stack>
#include <vector>
#include <fstream>
#include <GL/glew.h>

#include "tgt/camera.h"
#include "tgt/init.h"
#include "tgt/matrix.h"
#include "tgt/texture.h"
#include "tgt/transfuncintensity.h"
#include "tgt/transfunc.h"
#include "tgt/vector.h"



#include <Streams.h>	// This must be included before other DirectShow headers heaven knows why.
#include <DShow.h>
#include <DShowUtil.h>
#include <Dbt.h>
#include <InitGuid.h>
#include <Ks.h>
#include <KsProxy.h>
#include <ObjBase.h>
#include <amvideo.h>
#include <dvdmedia.h>
#include <smartptr.h>
#include <strsafe.h>
#include "boost/chrono.hpp"
#include "boost/bimap.hpp"
#include "boost/config.hpp"
#include "boost/optional.hpp"

#include "itkBoundingBox.h"
#include "itkEventObject.h"
#include "itkMutexLock.h"
#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkObject.h"
#include "itkPoint.h"
#include "itkVector.h"

#include "vnl/vnl_inverse.h"
#include "vtk3DS.h"
#include "vtk3DWidget.h"
#include "vtkAbstractWidget.h"
#include "vtkActor.h"
#include "vtkActorCollection.h"
#include "vtkAxesActor.h"
#include "vtkAxisActor2D.h"
#include "vtkBoxWidget.h"
#include "vtkCamera.h"
#include "vtkCaptionActor2D.h"
#include "vtkCellArray.h"
#include "vtkCommand.h"
#include "vtkCullerCollection.h"
#include "vtkConeSource.h"
#include "vtkCoordinate.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkDistanceWidget.h"
#include "vtkFloatArray.h"
#include "vtkFollower.h"
#include "vtkImporter.h"
#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLineSource.h"
#include "vtkLineWidget2.h"
#include "vtkMapper.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkOpenGLActor.h"
#include "vtkOpenGLRenderer.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricSpline.h"
#include "vtkParametricTorus.h"
#include "vtkPicker.h"
#include "vtkPlane.h"
#include "vtkPlaneSource.h"
#include "vtkPlaneWidget.h"
#include "vtkPointData.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkPolyData.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkPolyDataMapper.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkProp3D.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkTextActor.h"
#include <vtkTextProperty.h>
#include "vtkTexturedActor2D.h"
#include "vtkTimerLog.h"
#include "vtkTransform.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"

#include "igstkEvents.h"
#include "igstkPulseGenerator.h"
#include "igstkTracker.h"
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
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkHistogram.h"
#include <itkImageToHistogramFilter.h>
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"


#include "TinyXml/tinyxml.h"

#include "Serialization/serializable.h"
#include "Serialization/xmldeserializer.h"
#include "Serialization/xmlserializer.h"

#include "voreen/canvasrenderer.h"
#include "voreen/multivolumeproxygeometry.h"
#include "voreen/multivolumeraycaster.h"
#include "voreen/observer.h"
#include "voreen/processor.h"
#include "voreen/property.h"
#include "voreen/volumehandle.h"

#pragma warning (pop)