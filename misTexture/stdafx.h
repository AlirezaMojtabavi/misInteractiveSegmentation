
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
//#include "MySpeedFunction3D.h"

#include "TinyXml//tinyxml.h"

#include "tgt/TransFuncIntensity.h"
#include "tgt/gpucapabilities.h"
#include "tgt/texture.h"
#include "tgt/vector.h"

#include "Serialization/xmlserializer.h"
#include "Serialization/xmldeserializer.h"

